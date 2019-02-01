//
// Created by djang on 2019-01-29.
//

#include "Sphere.h"
#include "Ray.h"
#include "Material.h"

#define ENABLE_OPTIMIZATION 1

Sphere::Sphere()
        : m_center { 0.0f }, m_radius { 0.0f } {
}

Sphere::Sphere(const Vec3<float> &center, float radius, std::unique_ptr <Material> pMaterial)
        : m_center { center }, m_radius { radius }, m_pMaterial { std::move(pMaterial) } {
}

std::optional <HitInfo> Sphere::hit(const Ray &ray, float minTime, float maxTime) const {
    auto CO = ray.origin - m_center;

    float a = dot(ray.direction, ray.direction);

#if ENABLE_OPTIMIZATION
    float b = dot(CO, ray.direction);
#else
    float b = 2.0f * dot(CO, ray.direction);
#endif //ENABLE_OPTIMIZATION

    float c = dot(CO, CO) - (m_radius * m_radius);

#if ENABLE_OPTIMIZATION
    auto disc2 = (b * b) - (a * c);
#else
    auto disc2 = (b * b) - (4.0f * a * c);
#endif //ENABLE_OPTIMIZATION

    if (disc2 < 0.0f)
        return std::nullopt;

    float disc = sqrtf(disc2);
#if ENABLE_OPTIMIZATION
    float time = (-b - disc) / a;
#else
    float time = (-b - disc) / (2.0f * a);
#endif //ENABLE_OPTIMIZATION

    if (minTime < time && time < maxTime) {
        auto position = ray.getPointAt(time);
        auto normal = (position - m_center) / m_radius;

        return HitInfo { time, position, normal, m_pMaterial.get() };
    }

#if ENABLE_OPTIMIZATION
    time = (-b + disc) / a;
#else
    time = (-b + disc) / (2.0f * a);
#endif //ENABLE_OPTIMIZATION

    if (minTime < time && time < maxTime) {
        auto position = ray.getPointAt(time);
        auto normal = (position - m_center) / m_radius;

        return HitInfo { time, position, normal, m_pMaterial.get() };
    }

    return std::nullopt;
}

const Vec3<float> &Sphere::getCenter() const noexcept {
    return m_center;
}

float Sphere::getRadius() const noexcept {
    return m_radius;
}

Sphere &Sphere::setCenter(const Vec3<float> &center) noexcept {
    m_center = center;
    return *this;
}

Sphere &Sphere::setRadius(float radius) noexcept {
    m_radius = radius;
    return *this;
}

Sphere &Sphere::setMaterial(std::unique_ptr<Material> pMaterial) noexcept {
    m_pMaterial = std::move(pMaterial);
    return *this;
}
