//
// Created by Daemyung Jang on 2019-01-28.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H


#include "Vector.hpp"

struct Ray {
    Vec3<float> origin;
    Vec3<float> direction;

    Ray() noexcept;

    Ray(const Vec3<float> &origin, const Vec3<float> &direction) noexcept;

    Vec3<float> getPointAt(float time) const noexcept;
};


#endif //RAY_TRACING_RAY_H
