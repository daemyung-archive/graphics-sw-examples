//
// Created by djang on 2019-01-31.
//

#ifndef RAY_TRACING_METAL_H
#define RAY_TRACING_METAL_H


#include "Material.h"
#include "Vector.hpp"

class Metal : public Material {
public:
    Metal(const Vec3<float> &albedo, float fuzz = 0.0f);

    std::optional<ScatterInfo> scatter(const Ray &ray, const HitInfo &hitInfo) const;

private:
    Vec3<float> m_albedo;
    float m_fuzz;
};


#endif //RAY_TRACING_METAL_H
