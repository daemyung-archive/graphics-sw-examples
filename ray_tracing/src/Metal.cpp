//
// Created by djang on 2019-01-31.
//

#include "Metal.h"

#include <cmath>
#include <algorithm>

#include "Ray.h"

namespace {
    Vec3<float> reflect(const Vec3<float> &input, const Vec3<float> &normal) {
        return input + (2.0f * dot(-input, normal) * normal);
    }
}

Metal::Metal(const Vec3<float> &albedo, float fuzz)
        : m_albedo { albedo }, m_fuzz { std::min(fuzz, 1.0f) } {
}

std::optional<ScatterInfo> Metal::scatter(const Ray &ray, const HitInfo &hitInfo) const {
    auto reflected = reflect(normalize(ray.direction), hitInfo.normal);
    reflected += m_fuzz * getRandomPositionInUnitSphere();

    if (0.0f > dot(reflected, hitInfo.normal))
        return std::nullopt;

    return ScatterInfo {
            m_albedo,
            Ray { hitInfo.position, reflected }
    };
}
