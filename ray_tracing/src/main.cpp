//
// Created by Daemyung Jang on 2019-01-28.
//

#include <memory>
#include <array>
#include <random>
#include <future>
#include <algorithm>

#include "Vector.hpp"
#include "Pixmap.h"
#include "Ray.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

#define USE_MULTI_THREAD 1

namespace {

    constexpr auto kResolution = Vec2<uint32_t> { 500, 250 };
    constexpr auto kSampleCount = 16;
    constexpr auto kMaxDepth = 50;

#if USE_MULTI_THREAD
    constexpr auto kThreadCount = 25;
#endif
};

HitableList generateRandomScene() {
    std::vector<std::unique_ptr<Hitable>> list;

    list.push_back(std::make_unique<Sphere>(
            Vec3<float> { 0.0f, -1000.0f, 0.0f }, 1000.0f,
            std::make_unique<Lambertian>(Vec3<float> { 0.5f, 0.5f, 0.5f })
    ));

    std::random_device generator;
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    for (auto x = -11; x != 11; ++x)
        for (auto z = -11; z != 11; ++z) {
            Vec3<float> center = {
                    x + 0.9f * distribution(generator),
                    0.2f,
                    z + 0.9f * distribution(generator)
            };

            float chance = distribution(generator);

            if ((center - Vec3<float> { 4.0f, 0.2f, 0.0f }).length() > 0.9f) {
                if (chance < 0.8f) {
                    Vec3<float> albedo = {
                            distribution(generator) * distribution(generator),
                            distribution(generator) * distribution(generator),
                            distribution(generator) * distribution(generator)
                    };

                    list.push_back(std::make_unique<Sphere>(
                            center, 0.2f,
                            std::make_unique<Lambertian>(albedo)
                    ));
                } else if (chance < 0.95f) {
                    Vec3<float> albedo = {
                            0.5f * (1.0f + distribution(generator)),
                            0.5f * (1.0f + distribution(generator)),
                            0.5f * (1.0f + distribution(generator))
                    };

                    list.push_back(std::make_unique<Sphere>(
                            center, 0.2f,
                            std::make_unique<Metal>(albedo, 0.5f * distribution(generator))
                    ));
                } else {
                    list.push_back(std::make_unique<Sphere>(
                            center, 0.2f,
                            std::make_unique<Dielectric>(1.5f)
                    ));
                }
            }
    }

    list.push_back(std::make_unique<Sphere>(
            Vec3<float> { 0.0f, 1.0f, 0.0f }, 1.0f,
            std::make_unique<Dielectric>(1.5f)
    ));

    list.push_back(std::make_unique<Sphere>(
            Vec3<float> { -2.0f, 1.0f, 0.0f }, 1.0f,
            std::make_unique<Lambertian>(Vec3<float> { 0.5f, 0.2f, 0.1f })
    ));

    list.push_back(std::make_unique<Sphere>(
            Vec3<float> { 2.0f, 1.0f, 0.0f }, 1.0f,
            std::make_unique<Metal>(Vec3<float> { 0.7f, 0.6f, 0.5f }, 0.0f)
    ));

    return HitableList { std::move(list) };
}

Vec3<float> calcColor(const Ray &ray, HitableList &world, int depth) {
    auto hitResult = world.hit(ray, std::numeric_limits<float>::epsilon(), std::numeric_limits<float>::max());

    if (hitResult.has_value()) {
        auto hitInfo = hitResult.value();
        auto scatterResult = hitInfo.pMaterial->scatter(ray, hitInfo);

        if (depth > kMaxDepth || !scatterResult.has_value())
            return Vec3<float> { 0.0f };

        auto scatterInfo = scatterResult.value();

        return scatterInfo.attenuation * calcColor(scatterInfo.ray, world, depth + 1);
    } else {
        auto unitDir = normalize(ray.direction);
        auto t = 0.5f * (unitDir.y + 1.0f);

        constexpr auto kWhite = Vec3<float> { 1.0f, 1.0f, 1.0f };
        constexpr auto kSky = Vec3<float> { 0.5f, 0.7f, 1.0f };

        return (1.0f - t) * kWhite + t * kSky;
    }
}

#if USE_MULTI_THREAD
struct Tile {
    Vec2<int> offset;
    Vec2<int> size;
};

void render(Camera &camera, HitableList &world, Pixmap &buffer, const Tile &tile) {
    for (int y = tile.size.height + tile.offset.y - 1; y >= tile.offset.y; --y)
        for (int x = 0; x < tile.size.width + tile.offset.x; ++x) {
            auto color = Vec3<float> { 0.0f };

            std::random_device generator;
            std::uniform_real_distribution<float> distribution(0.0f, 1.0f - std::numeric_limits<float>::epsilon());

            for (auto i = 0; i != kSampleCount; ++i) {
                Vec2<float> coord = {
                        (x + distribution(generator)) / static_cast<float>(kResolution.width),
                        (y + distribution(generator)) / static_cast<float>(kResolution.height)
                };

                auto ray = camera.getRay(coord);
                color += calcColor(ray, world, 0);
            }

            color /= kSampleCount;

            constexpr auto kGamma = 2.4f;
            color = gammaCorrect(color, kGamma);

            auto pixel = static_cast<Pixmap::PixelType>(color);
            buffer.setPixel(x, y, pixel);
        }
}
#endif

int main(int argc, char *argv[]) {
    Pixmap backBuffer { kResolution.width, kResolution.height };

    HitableList world = generateRandomScene();

    // Camera variables
    constexpr auto kLookFrom = Vec3<float> { 3.0f, 1.0f, 2.0f };
    constexpr auto kLookAt = Vec3<float> { 0.0f, 0.0f, -1.0f };
    constexpr auto kYAxis = Vec3<float> { 0.0f, 1.0f, 0.0f };
    const auto kVFov = 90.0f;
    const auto kAspect = kResolution.width / static_cast<float>(kResolution.height);

    Camera camera {
            kLookFrom, kLookAt, kYAxis, kVFov, kAspect,
    };

#if USE_MULTI_THREAD
    assert(0 == kResolution.height % kThreadCount);

    std::vector<std::future<void>> results;

    for (auto i = 0; i != kThreadCount; ++i) {
        int yOffset = kResolution.height / kThreadCount;

        Tile tile = {
                Vec2<int> { 0, yOffset * i },
                Vec2<int> { static_cast<int>(kResolution.width), yOffset }
        };

        results.push_back(std::async(render, std::ref(camera), std::ref(world), std::ref(backBuffer), tile));
    }

    std::for_each(std::begin(results), std::end(results), [](std::future<void> &result) { result.wait(); });
#else
    for (int y = kResolution.height - 1; y >= 0; --y)
        for (int x = 0; x < kResolution.width; ++x) {
            auto color = Vec3<float> { 0.0f };

            std::random_device generator;
            std::uniform_real_distribution<float> distribution(0.0f, 1.0f - std::numeric_limits<float>::epsilon());

            for (auto i = 0; i != kSampleCount; ++i) {
                Vec2<float> coord = {
                        (x + distribution(generator)) / static_cast<float>(kResolution.width),
                        (y + distribution(generator)) / static_cast<float>(kResolution.height)
                };

                auto ray = camera.getRay(coord);
                color += calcColor(ray, world, 0);
            }

            color /= kSampleCount;

            constexpr auto kGamma = 2.4f;
            color = gammaCorrect(color, kGamma);

            auto pixel = static_cast<Pixmap::PixelType>(color);
            backBuffer.setPixel(x, y, pixel);
        }
#endif

    backBuffer.save("result.png");

    return 0;
}