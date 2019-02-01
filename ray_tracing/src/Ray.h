//
// Created by Daemyung Jang on 2019-01-28.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H


#include "Vector.hpp"

struct Ray {
    using VecType = Vec3<float>;

    VecType origin;
    VecType direction;

    Ray() noexcept;

    Ray(const VecType &origin, const VecType &direction) noexcept;

    VecType getPointAt(float time) const noexcept;
};


#endif //RAY_TRACING_RAY_H
