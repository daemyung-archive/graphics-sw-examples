//
// Created by Daemyung Jang on 2019-01-28.
//

#include "Pixmap.h"

#include <cassert>
#include <regex>
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

Pixmap::Pixmap(uint32_t width, uint32_t height)
        : m_width { width }, m_height { height }, m_pixels { } {
    m_pixels.resize(m_width * m_height);
}

Pixmap &Pixmap::setPixel(uint32_t x, uint32_t y, const PixelType &pixel) {
    m_pixels[y * m_width + x] = pixel;

    return *this;
}

void Pixmap::save(const std::string &fileName) const {
    const auto ext = fileName.substr(fileName.length() - 3);

    std::vector<Vec3<uint8_t>> rgbs;
    for (auto &pixel : m_pixels) {
        constexpr auto kMin = 0.0f;
        constexpr auto kMax = 255.0f;

        Vec3<uint8_t> rgb {
                static_cast<uint8_t>(std::clamp(pixel.x * kMax, kMin, kMax)),
                static_cast<uint8_t>(std::clamp(pixel.y * kMax, kMin, kMax)),
                static_cast<uint8_t>(std::clamp(pixel.z * kMax, kMin, kMax))
        };

        rgbs.push_back(rgb);
    }

    stbi_flip_vertically_on_write(true);

    if ("png" == ext) {
        stbi_write_png(fileName.c_str(), m_width, m_height, STBI_rgb, rgbs.data(), STBI_rgb * m_width);
    } else {
        assert(false);
    }

    stbi_flip_vertically_on_write(false);
}

uint32_t Pixmap::getWidth() const noexcept {
    return m_width;
}

uint32_t Pixmap::getHeight() const noexcept {
    return m_height;
}

