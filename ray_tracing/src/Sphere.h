//
// Created by djang on 2019-01-29.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H


#include <memory>

#include "Hitable.h"
#include "Vector.hpp"

class Material;

class Sphere : public Hitable {
public:
    Sphere();

    Sphere(const Vec3<float> &center, float radius, std::unique_ptr<Material> pMaterial);

    std::optional<HitInfo> hit(const Ray &ray, float minTime, float maxTime) const;

    const Vec3<float> &getCenter() const noexcept;

    float getRadius() const noexcept;

    Sphere &setCenter(const Vec3<float> &center) noexcept;

    Sphere &setRadius(float radius) noexcept;

    Sphere &setMaterial(std::unique_ptr<Material> pMaterial) noexcept;

private:
    Vec3<float> m_center;
    float m_radius;
    std::unique_ptr<Material> m_pMaterial;
};


#endif //RAY_TRACING_SPHERE_H
