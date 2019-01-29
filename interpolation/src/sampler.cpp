// MIT License
// 
// Copyright(c) 2018 Jang daemyung
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "sampler.h"

#include <cassert>
#include <array>
#include <algorithm>

#include "image.h"

Sampler::Sampler(FilterType filter)
	:
	mFilter { filter }
{
}

Color Sampler::GetTexture(const Image& image, const glm::vec2& st)
{
	auto color = glm::vec4 { 0.0, 0.0, 0.0, 0.0 };

	switch (mFilter)
	{
	case FilterType::Nearest:
		color = GetTextureUsingNearest(image, st);
		break;

	case FilterType::Linear:
		color = GetTextureUsingLinear(image, st);
		break;

    case FilterType::Cubic:
        color = GetTextureUsingCubic(image, st);
        break;

	default:
		assert(false);
		break;
	}

	return color;
}

Color Sampler::GetTextureUsingNearest(const Image& image, const glm::vec2& st)
{
    const auto size  = glm::vec2 { image.GetWidth() - 1, image.GetHeight() - 1 };
    const auto coord = static_cast<glm::uvec2>(st * size);
	
	return image.GetPixel(coord.x, coord.y);
}

Color Sampler::GetTextureUsingLinear(const Image& image, const glm::vec2& st)
{
    const auto size  = glm::vec2 { image.GetWidth() - 1, image.GetHeight() - 1 };
    const auto coord = static_cast<glm::uvec2>(st * size);

    // -------------
    // | c00 | c10 | Delta is the weight how much each pixels will be contribued.
    // ------X------ For example, X is a sampling location then the delta is (0.5, 0.5).
    // | c01 | c11 | The result color has the quarter of each pixel.
    // -------------
    auto GetPixel = [&](const Image& image, const glm::uvec2& coord)
    {
        const auto clampedCoord = GetCoordUsingClampToEdge(image, glm::uvec2 { coord.x, coord.y });
        return image.GetPixel(clampedCoord.x, clampedCoord.y);
    };
    
    const auto c00   = GetPixel(image, glm::uvec2 { coord.x + 0, coord.y + 0 });
    const auto c10   = GetPixel(image, glm::uvec2 { coord.x + 1, coord.y + 0 });
    const auto c01   = GetPixel(image, glm::uvec2 { coord.x + 0, coord.y + 1 });
    const auto c11   = GetPixel(image, glm::uvec2 { coord.x + 1, coord.y + 1 });
    const auto delta = st * size - static_cast<glm::vec2>(coord);

    auto LinearInterpolation = [](const Color& c0, const Color& c1, float a)
    {
        auto color = static_cast<glm::vec4>(c0) * (1.0f - a) + static_cast<glm::vec4>(c1) * a;
        return static_cast<Color>(color);
    };

    return LinearInterpolation(LinearInterpolation(c00, c10, delta.x),
                               LinearInterpolation(c01, c11, delta.x),
                               delta.y);
}

Color Sampler::GetTextureUsingCubic(const Image& image, const glm::vec2& st)
{
    const auto size  = glm::vec2 { image.GetWidth() - 1, image.GetHeight() - 1 };
    const auto coord = static_cast<glm::uvec2>(st * size);

    // -------------------------
    // | c00 | c10 | c20 | c30 |
    // ------+-----+-----+------
    // | c01 | c11 | c21 | c31 |
    // ------+-----+-----+------
    // | c02 | c12 | c22 | c32 |
    // ------+-----+-----+------
    // | c03 | c13 | c23 | c33 |
    // -------------------------
    auto GetPixel = [&](const Image& image, const glm::uvec2& coord)
    {
        const auto clampedCoord = GetCoordUsingClampToEdge(image, glm::uvec2 { coord.x, coord.y });
        return image.GetPixel(clampedCoord.x, clampedCoord.y);
    };

    const auto c00   = GetPixel(image, glm::uvec2 { coord.x - 1, coord.y - 1 });
    const auto c10   = GetPixel(image, glm::uvec2 { coord.x + 0, coord.y - 1 });
    const auto c20   = GetPixel(image, glm::uvec2 { coord.x + 1, coord.y - 1 });
    const auto c30   = GetPixel(image, glm::uvec2 { coord.x + 2, coord.y - 1 });
    const auto c01   = GetPixel(image, glm::uvec2 { coord.x - 1, coord.y + 0 });
    const auto c11   = GetPixel(image, glm::uvec2 { coord.x + 0, coord.y + 0 });
    const auto c21   = GetPixel(image, glm::uvec2 { coord.x + 1, coord.y + 0 });
    const auto c31   = GetPixel(image, glm::uvec2 { coord.x + 2, coord.y + 0 });
    const auto c02   = GetPixel(image, glm::uvec2 { coord.x - 1, coord.y + 1 });
    const auto c12   = GetPixel(image, glm::uvec2 { coord.x + 0, coord.y + 1 });
    const auto c22   = GetPixel(image, glm::uvec2 { coord.x + 1, coord.y + 1 });
    const auto c32   = GetPixel(image, glm::uvec2 { coord.x + 2, coord.y + 1 });
    const auto c03   = GetPixel(image, glm::uvec2 { coord.x - 1, coord.y + 2 });
    const auto c13   = GetPixel(image, glm::uvec2 { coord.x + 0, coord.y + 2 });
    const auto c23   = GetPixel(image, glm::uvec2 { coord.x + 1, coord.y + 2 });
    const auto c33   = GetPixel(image, glm::uvec2 { coord.x + 2, coord.y + 2 });
    const auto delta = st * size - static_cast<glm::vec2>(coord);
    
    auto CubicInterpolation = [](const Color& c0, const Color& c1, const Color& c2, const Color& c3, float x)
    {
        const auto p0 = static_cast<glm::vec4>(c0);
        const auto p1 = static_cast<glm::vec4>(c1);
        const auto p2 = static_cast<glm::vec4>(c2);
        const auto p3 = static_cast<glm::vec4>(c3);

        auto color = p1 + 0.5f * x * (p2 - p0 + x * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3 + x * (3.0f * (p1 - p2) + p3 - p0)));
        return static_cast<Color>(glm::clamp(color, glm::vec4(0.0f), glm::vec4(255.0f)));
    };

    return CubicInterpolation(CubicInterpolation(c00, c10, c20, c30, delta.x),
                              CubicInterpolation(c01, c11, c21, c31, delta.x),
                              CubicInterpolation(c02, c12, c22, c32, delta.x),
                              CubicInterpolation(c03, c13, c23, c33, delta.x),
                              delta.y);
}

glm::uvec2 Sampler::GetCoordUsingReapeat(const Image& image, const glm::uvec2& coord)
{
	return glm::uvec2{ coord.x % image.GetWidth(), coord.y % image.GetWidth() };
}

glm::uvec2 Sampler::GetCoordUsingClampToEdge(const Image& image, const glm::uvec2& coord)
{
    return glm::uvec2 { std::clamp(coord.x, 0u, image.GetWidth()  - 1),
                        std::clamp(coord.y, 0u, image.GetHeight() - 1) };
}