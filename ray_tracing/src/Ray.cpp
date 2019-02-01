//
// Created by Daemyung Jang on 2019-01-28.
//

#include "Ray.h"

Ray::Ray() noexcept
        : origin { 0.0f }, direction { 0.0f } {

}

Ray::Ray(const Vec3<float> &origin, const Vec3<float> &direction) noexcept
        : origin { origin }, direction { direction } {

}

Vec3<float> Ray::getPointAt(float time) const noexcept {
    return origin + (direction * time);
}
