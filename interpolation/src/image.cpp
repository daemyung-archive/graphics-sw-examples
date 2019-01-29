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

#include "image.h"

#include <cassert>
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

Image::Image(const glm::uvec2& size)
	:
	mSize   { size            },
	mBuffer { size.x * size.y }
{
}

void Image::Write(const std::string& name) const
{
	auto extension = name.substr(name.length() - 3);

	stbi_flip_vertically_on_write(true);

	if ("bmp" == extension)
	{
		stbi_write_bmp(name.c_str(), GetWidth(), GetHeight(), STBI_rgb_alpha, mBuffer.data());
	}
	else if ("png" == extension)
	{
		stbi_write_png(name.c_str(), GetWidth(), GetHeight(), STBI_rgb_alpha, mBuffer.data(), GetHeight() * sizeof(Color::value_type));
	}
	else
	{
		assert(false);
	}

	stbi_flip_vertically_on_write(false);
}