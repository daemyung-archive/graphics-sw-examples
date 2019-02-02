//
// Created by djang on 2019-01-29.
//

#ifndef RAY_TRACING_HITABLE_H
#define RAY_TRACING_HITABLE_H


#include "Optional.hpp"
#include "Vector.hpp"

struct Ray;

class Material;

struct HitInfo {
    float time;
    Vec3<float> position;
    Vec3<float> normal;
    Material *pMaterial;

    HitInfo();

    HitInfo(float time, const Vec3<float> &position, const Vec3<float> &normal, Material *pMaterial);

    HitInfo &setTime(float time);

    HitInfo &setPosition(const Vec3<float> &position);

    HitInfo &setNormal(const Vec3<float> &normal);

    HitInfo &setMaterial(Material *pMaterial);
};

class Hitable {
public:
    virtual ~Hitable() = default;

    virtual std::optional<HitInfo> hit(const Ray &ray, float minTime, float maxTime) const = 0;
};


#endif //RAY_TRACING_HITABLE_H
