//
// Created by Daemyung Jang on 2019-01-28.
//

#ifndef RAY_TRACING_VECTOR_H
#define RAY_TRACING_VECTOR_H


#include <cassert>
#include <cmath>
#include <limits>
#include <optional>

template<typename T>
struct Vec2 {
    union {
        T x;
        T u;
        T width;
    };

    union {
        T y;
        T v;
        T height;
    };

    constexpr Vec2() = default;

    constexpr Vec2(T s) noexcept
            : x { s }, y { s } {
    }

    constexpr Vec2(T x, T y) noexcept
            : x { x }, y { y } {
    }
};

template<typename T>
struct Vec3 {
    union {
        T x;
        T r;
        T width;
    };

    union {
        T y;
        T g;
        T height;
    };

    union {
        T z;
        T b;
        T depth;
    };

    constexpr Vec3() = default;

    constexpr Vec3(T s) noexcept
            : x { s }, y { s }, z { s } {
    }

    constexpr Vec3(T x, T y, T z) noexcept
            : x { x }, y { y }, z { z } {
    }

    template<typename U>
    explicit operator Vec3<U>() const {
        return Vec3<U> {
                static_cast<U>(x * std::numeric_limits<U>::max()),
                static_cast<U>(y * std::numeric_limits<U>::max()),
                static_cast<U>(z * std::numeric_limits<U>::max())
        };
    }

    inline Vec3 operator+() const noexcept {
        return Vec3 { x, y, z };
    }

    inline Vec3 operator-() const noexcept {
        return Vec3 { -x, -y, -z };
    }

    inline Vec3 &operator+=(T s) noexcept {
        x += s;
        y += s;
        z += s;

        return *this;
    }

    inline Vec3 &operator-=(T s) noexcept {
        x -= s;
        y -= s;
        z -= s;

        return *this;
    }

    inline Vec3 &operator*=(T s) noexcept {
        x *= s;
        y *= s;
        z *= s;

        return *this;
    }

    inline Vec3 &operator/=(T s) noexcept {
        x /= s;
        y /= s;
        z /= s;

        return *this;
    }

    inline Vec3 &operator+=(const Vec3 &v) noexcept {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }

    inline Vec3 &operator-=(const Vec3 &v) noexcept {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    inline Vec3 &operator*=(const Vec3 &v) noexcept {
        x *= v.x;
        y *= v.y;
        z *= v.z;

        return *this;
    }

    inline Vec3 &operator/=(const Vec3 &v) noexcept {
        x /= v.x;
        y /= v.y;
        z /= v.z;

        return *this;
    }

    inline Vec3 operator+(T s) const noexcept {
        return Vec3 { x + s, y + s, z + s };
    }

    inline Vec3 operator-(T s) const noexcept {
        return Vec3 { x - s, y - s, z - s };
    }

    inline Vec3 operator*(T s) const noexcept {
        return Vec3 { x * s, y * s, z * s };
    }

    inline Vec3 operator/(T s) const noexcept {
        return Vec3 { x / s, y / s, z / s };
    }

    inline Vec3 operator+(const Vec3 &v) const noexcept {
        return Vec3 { x + v.x, y + v.y, z + v.z };
    }

    inline Vec3 operator-(const Vec3 &v) const noexcept {
        return Vec3 { x - v.x, y - v.y, z - v.z };
    }

    inline Vec3 operator*(const Vec3 &v) const noexcept {
        return Vec3 { x * v.x, y * v.y, z * v.z };
    }

    inline Vec3 operator/(const Vec3 &v) const noexcept {
        return Vec3 { x / v.x, y / v.y, z / v.z };
    }

    inline float length2() const noexcept {
        return (x * x) + (y * y) + (z * z);
    }

    inline float length() const noexcept {
        return std::sqrt(length2());
    }

    inline void normalize() const noexcept {
        operator/=(1.0f / length());
    }

    inline float dot(const Vec3 &v) const noexcept {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }

    inline Vec3 cross(const Vec3 &v) const noexcept {
        return Vec3 { (y * v.z) - (z * v.y), -((x * v.z) - (z * v.x)), (x * v.y) - (y * v.x) };
    }
};

template<typename T>
inline Vec3<T> operator+(T s, const Vec3<T> &v) noexcept {
    return v + s;
}

template<typename T>
inline Vec3<T> operator-(T s, const Vec3<T> &v) noexcept {
    return v - s;
}

template<typename T>
inline Vec3<T> operator*(T s, const Vec3<T> &v) noexcept {
    return v * s;
}

template<typename T>
inline Vec3<T> operator/(T s, const Vec3<T> &v) noexcept {
    return v / s;
}

template<typename T>
inline Vec3<T> normalize(const Vec3<T> &v) noexcept {
    return v / v.length();
}

template<typename T>
inline T dot(const Vec3<T> &v1, const Vec3<T> &v2) noexcept {
    return v1.dot(v2);
}

template<typename T>
inline Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2) noexcept {
    return v1.cross(v2);
}

template<typename T>
inline Vec3<T> gammaCorrect(const Vec3<T> &v, T gamma) noexcept {
    static_assert(std::is_floating_point_v<T>);

    const auto kExponent = static_cast<T>(1.0f) / gamma;

    if constexpr (std::is_same_v<float, T>)
        return Vec3<T> { powf(v.x, kExponent), powf(v.y, kExponent), powf(v.z, kExponent) };
    else
        return Vec3<T> { pow(v.x, kExponent), pow(v.y, kExponent), pow(v.z, kExponent) };
}

template<typename T>
inline Vec3<T> reflect(const Vec3<T> &i, const Vec3<T> &n) {
    constexpr auto kEpsilon = std::numeric_limits<T>::epsilon() * 1.5f;

    assert(1.0f - kEpsilon <= i.length() && i.length() <= 1.0f + kEpsilon);
    assert(1.0f - kEpsilon <= n.length() && n.length() <= 1.0f + kEpsilon);

    return i + (2.0f * dot(-i, n) * n);
}

template<typename T>
inline std::optional<Vec3<T>> refract(const Vec3<T> &i, const Vec3<T> &n, float eta) {
    constexpr auto kEpsilon = std::numeric_limits<T>::epsilon() * 1.5f;

    assert(1.0f - kEpsilon <= i.length() && i.length() <= 1.0f + kEpsilon);
    assert(1.0f - kEpsilon <= n.length() && n.length() <= 1.0f + kEpsilon);

    float s = dot(n, i);
    float k = 1.0f - eta * eta * (1.0f - s * s);
    if (k < 0.0f)
        return std::nullopt;
    else
        return eta * i - (eta * s + sqrtf(k)) * n;
}


#endif //RAY_TRACING_VECTOR_H
