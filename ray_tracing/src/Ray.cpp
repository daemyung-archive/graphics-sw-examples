//
// Created by Daemyung Jang on 2019-01-28.
//

#include "Ray.h"

Ray::Ray() noexcept
        : origin { 0.0f }, direction { 0.0f } {

}

Ray::Ray(const VecType &origin, const VecType &direction) noexcept
        : origin { origin }, direction { direction } {

}

Ray::VecType Ray::getPointAt(float time) const noexcept {
    return origin + (direction * time);
}
