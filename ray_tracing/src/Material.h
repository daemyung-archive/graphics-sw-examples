//
// Created by djang on 2019-01-31.
//

#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H


#include "Optional.hpp"
#include "Vector.hpp"
#include "Ray.h"
#include "Hitable.h"

struct ScatterInfo {
    Vec3<float> attenuation;
    Ray ray;

    ScatterInfo();

    ScatterInfo(const Vec3<float> &attenuation, const Ray &ray);

    ScatterInfo &setAttenuation(const Vec3<float> &attenuation);

    ScatterInfo &setRay(const Ray &ray);
};

class Material {
public:
    virtual ~Material() = default;

    virtual std::optional<ScatterInfo> scatter(const Ray &ray, const HitInfo &hitInfo) const = 0;

protected:
    Vec3<float> getRandomPositionInUnitSphere() const noexcept;
};


#endif //RAY_TRACING_MATERIAL_H
