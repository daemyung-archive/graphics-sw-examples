//
// Created by djang on 2019-01-31.
//

#ifndef RAY_TRACING_DIELECTRIC_H
#define RAY_TRACING_DIELECTRIC_H


#include "Material.h"

class Dielectric : public Material {
public:
    Dielectric(float reflectIndex);

    std::optional<ScatterInfo> scatter(const Ray &ray, const HitInfo &hitInfo) const ;

private:
    float m_reflectIndex;
};


#endif //RAY_TRACING_DIELECTRIC_H
