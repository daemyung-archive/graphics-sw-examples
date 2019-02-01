//
// Created by djang on 2019-01-31.
//

#include <random>
#include "Dielectric.h"

namespace {

    float schlick(float cosine, float reflectIndex) {
        float r0 = (1 - reflectIndex) / (1 + reflectIndex);
        r0 *= r0;
        return r0 + (1 - r0) * powf((1.0f - cosine), 5.0f);
    }

}

Dielectric::Dielectric(float reflectIndex)
        : m_reflectIndex { reflectIndex } {
}

std::optional<ScatterInfo> Dielectric::scatter(const Ray &ray, const HitInfo &hitInfo) const {
    ScatterInfo scatterInfo;
    scatterInfo.setAttenuation(Vec3<float> { 1.0f, 1.0f, 1.0f });

    Vec3<float> normal { };
    float eta;
    float cosine;

    if (dot(ray.direction, hitInfo.normal) > 0.0f) {
        // From the air to the dielectric.
        normal = -hitInfo.normal;
        eta = m_reflectIndex;
        cosine = m_reflectIndex * dot(normalize(ray.direction), normalize(hitInfo.normal));
    } else {
        // From the dielectric to the air.
        normal = hitInfo.normal;
        eta = 1.0f / m_reflectIndex;
        cosine = -dot(normalize(ray.direction), normalize(hitInfo.normal));
    }

    auto refractResult = refract(normalize(ray.direction), normalize(normal), eta);
    float reflectProb = refractResult.has_value() ? schlick(cosine, m_reflectIndex) : 1.0f;

    std::random_device generator;
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    if (distribution(generator) < reflectProb)
        scatterInfo.setRay(Ray { hitInfo.position, reflect(normalize(ray.direction), normalize(hitInfo.normal)) });
    else
        scatterInfo.setRay(Ray { hitInfo.position, refractResult.value() });

    return scatterInfo;
}
