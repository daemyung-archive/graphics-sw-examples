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

#ifndef __SAMPLER_H__
#define __SAMPLER_H__

#include <glm/glm.hpp>

#include "types.h"

class Image;

class Sampler
{
public:
	enum class FilterType
	{
		Nearest,
		Linear,
        Cubic
	};

	Sampler(FilterType filter);

	Color GetTexture(const Image& image, const glm::vec2& st);

private:
	Color GetTextureUsingNearest(const Image& image, const glm::vec2& st);
	Color GetTextureUsingLinear (const Image& image, const glm::vec2& st);
    Color GetTextureUsingCubic  (const Image& image, const glm::vec2& st);

	glm::uvec2 GetCoordUsingReapeat    (const Image& image, const glm::uvec2& coord);
    glm::uvec2 GetCoordUsingClampToEdge(const Image& image, const glm::uvec2& coord);

private:
	FilterType mFilter;
};

#endif