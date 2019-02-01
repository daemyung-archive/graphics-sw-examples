//
// Created by djang on 2019-01-31.
//

#include "Material.h"

#include <random>

ScatterInfo::ScatterInfo()
        : attenuation { 0.0f }, ray { } {
}

ScatterInfo::ScatterInfo(const Vec3<float> &attenuation, const Ray &ray)
        : attenuation { attenuation }, ray { ray } {
}

ScatterInfo &ScatterInfo::setAttenuation(const Vec3<float> &attenuation) {
    this->attenuation = attenuation;
    return *this;
}

ScatterInfo &ScatterInfo::setRay(const Ray &ray) {
    this->ray = ray;
    return *this;
}

Vec3<float> Material::getRandomPositionInUnitSphere() const noexcept {
    Vec3<float> position { 0.0f };

    std::random_device generator;
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

    do {
        position.x = distribution(generator);
        position.y = distribution(generator);
        position.z = distribution(generator);
    } while (position.length() >= 1.0f);

    return position;
}
