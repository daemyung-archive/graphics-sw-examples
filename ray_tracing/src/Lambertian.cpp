//
// Created by djang on 2019-01-31.
//

#include "Lambertian.h"

Lambertian::Lambertian(const Vec3<float> &albedo)
        : m_albedo { albedo } {
}

std::optional<ScatterInfo> Lambertian::scatter(const Ray &ray, const HitInfo &hitInfo) const {
    Vec3<float> target = hitInfo.position + hitInfo.normal + getRandomPositionInUnitSphere();

    return ScatterInfo {
            m_albedo,
            Ray { hitInfo.position, target - hitInfo.position }
    };
}
