//
// Created by djang on 2019-01-31.
//

#ifndef RAY_TRACING_LAMBERTIAN_H
#define RAY_TRACING_LAMBERTIAN_H


#include "Material.h"
#include "Vector.hpp"

class Lambertian : public Material {
public:
    Lambertian(const Vec3<float> &albedo);

    std::optional<ScatterInfo> scatter(const Ray &ray, const HitInfo &hitInfo) const;

private:
    Vec3<float> m_albedo;
};


#endif //RAY_TRACING_LAMBERTIAN_H
