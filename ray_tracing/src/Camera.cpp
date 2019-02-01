//
// Created by djang on 2019-01-30.
//

#include "Camera.h"

#include <cmath>
#include <random>

namespace {

    Vec3<float> getRandomPositionInUnitDisk() {
        std::random_device generator;
        std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

        Vec3<float> position = { 0.0f };

        do {
            position.x = distribution(generator);
            position.y = distribution(generator);
        } while (dot(position, position) >= 1.0f);

        return position;
    }

}

Camera::Camera(const Vec3<float> &lookFrom, const Vec3<float> &lookAt, const Vec3<float> &up, float vFov, float aspect,
               float aperture, float focusDistance)
        : m_origin { lookFrom }, m_bottomLeft { 0.0f }, m_horizontal { 0.0f }, m_vertical { 0.0f },
          m_u { 0.0f }, m_v { 0.0f }, m_w { 0.0f }, m_lensRadius { aperture / 2.0f } {
    auto theta = static_cast<float>(vFov * M_PI / 180.0f);

    Vec2<float> halfSize { 0.0f };
    halfSize.height = tanf(theta / 2.0f);
    halfSize.width = halfSize.height * aspect;

    m_w = normalize(lookFrom - lookAt);
    m_u = normalize(cross(up, m_w));
    m_v = cross(m_w, m_u);

    m_bottomLeft = m_origin - halfSize.width * m_u * focusDistance - halfSize.height * m_v * focusDistance -
                   m_w * focusDistance;
    m_horizontal = 2.0f * halfSize.width * m_u * focusDistance;
    m_vertical = 2.0f * halfSize.height * m_v * focusDistance;
}

Ray Camera::getRay(float u, float v) const {
    auto randomDir = m_lensRadius * getRandomPositionInUnitDisk();
    auto offset = m_u * randomDir.x + m_v * randomDir.y;
    return Ray {
            m_origin + offset,
            m_bottomLeft + (u * m_horizontal) + (v * m_vertical) - m_origin - offset
    };
}

Ray Camera::getRay(const Vec2<float> &coord) const {
    return getRay(coord.u, coord.v);
}

Camera &Camera::setOrigin(const Vec3<float> &origin) {
    m_origin = origin;
    return *this;
}

Camera &Camera::setBottomLeft(const Vec3<float> &bottomLeft) {
    m_bottomLeft = bottomLeft;
    return *this;
}

Camera &Camera::setHorizontal(const Vec3<float> &horizontal) {
    m_horizontal = horizontal;
    return *this;
}

Camera &Camera::setVertical(const Vec3<float> &vertical) {
    m_vertical = vertical;
    return *this;
}
