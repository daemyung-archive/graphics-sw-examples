//
// Created by Daemyung Jang on 2019-01-28.
//

#ifndef RAY_TRACING_PIXMAP_H
#define RAY_TRACING_PIXMAP_H


#include <cstdint>
#include <string>
#include <vector>

#include "Vector.hpp"

class Pixmap {
public:
    using PixelType = Vec3<uint8_t>;

    Pixmap(uint32_t width, uint32_t height);

    Pixmap &setPixel(uint32_t x, uint32_t y, const PixelType &pixel);

    void save(const std::string &fileName) const;

    uint32_t getWidth() const noexcept;

    uint32_t getHeight() const noexcept;

private:
    uint32_t m_width;
    uint32_t m_height;
    std::vector<PixelType> m_pixels;
};


#endif //RAY_TRACING_PIXMAP_H
