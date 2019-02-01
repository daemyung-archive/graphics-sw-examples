//
// Created by djang on 2019-01-30.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H


#include "Vector.hpp"
#include "Ray.h"

class Camera {
public:
    Camera(const Vec3<float> &lookFrom, const Vec3<float> &lookAt, const Vec3<float> &up, float vFov, float aspect,
           float aperture = 0.0f, float focusDistance = 1.0f);

    Ray getRay(float u, float v) const;

    Ray getRay(const Vec2<float> &coord) const;

    Camera &setOrigin(const Vec3<float> &origin);

    Camera &setBottomLeft(const Vec3<float> &bottomLeft);

    Camera &setHorizontal(const Vec3<float> &horizontal);

    Camera &setVertical(const Vec3<float> &vertical);

private:
    Vec3<float> m_origin;
    Vec3<float> m_bottomLeft;
    Vec3<float> m_horizontal;
    Vec3<float> m_vertical;
    Vec3<float> m_u;
    Vec3<float> m_v;
    Vec3<float> m_w;
    float m_lensRadius;
};


#endif //RAY_TRACING_CAMERA_H
