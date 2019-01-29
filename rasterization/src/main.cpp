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

#include <algorithm>

#include "triangle.h"
#include "box.h"
#include "framebuffer.h"

void DrawTriangle(Triangle& triangle, Framebuffer& framebuffer, std::vector<float>& depthBuffer)
{
	auto TransformToScreenSpace = [](const glm::vec3& position)
	{
		return glm::vec2
		{
			position.x / position.z,
			position.y / position.z,
		};
	};

	auto scrV0 = TransformToScreenSpace(triangle[0].position);
	auto scrV1 = TransformToScreenSpace(triangle[1].position);
	auto scrV2 = TransformToScreenSpace(triangle[2].position);

	auto TransformToRasterSpace = [](const glm::vec2& position, const glm::uvec2& resolution)
	{
		return (1.0f + position) * 0.5f * static_cast<glm::vec2>(resolution);
	};

	auto res = glm::uvec2{ 512, 512 };

	auto rstV0 = glm::vec3{ TransformToRasterSpace(scrV0, res), triangle[0].position.z };
	auto rstV1 = glm::vec3{ TransformToRasterSpace(scrV1, res), triangle[1].position.z };
	auto rstV2 = glm::vec3{ TransformToRasterSpace(scrV2, res), triangle[2].position.z };

	auto GetBoundingBox = [](const glm::vec2& v0, const glm::vec2& v1, const glm::vec2& v2)
	{
		return Box
		{
			static_cast<int32_t>(std::floor(std::min(std::min(v0.y, v1.y), v2.y))),
			static_cast<int32_t>(std::floor(std::min(std::min(v0.x, v1.x), v2.x))),
			static_cast<int32_t>(std::ceil (std::max(std::max(v0.y, v1.y), v2.y))),
			static_cast<int32_t>(std::ceil (std::max(std::max(v0.x, v1.x), v2.x)))
		};
	};

	auto boundingBox = GetBoundingBox(rstV0, rstV1, rstV2);

	boundingBox.Clamp(0, 0, framebuffer.GetWidth() - 1, framebuffer.GetHeight() - 1);

	auto EdgeFunction = [](const glm::vec2& v0, const glm::vec2& v1, const glm::vec2& v2)
	{
		return glm::determinant(glm::mat2(v0 - v2, v1 - v2));
	};
	const float area = EdgeFunction(rstV0, rstV1, rstV2);

	for (auto y = boundingBox.GetTop(); y <= boundingBox.GetBottom(); ++y)
	{
		for (auto x = boundingBox.GetLeft(); x <= boundingBox.GetRight(); ++x)
		{
			auto position = glm::vec2{ x, y } +0.5f;

			const auto w0 = EdgeFunction(rstV1, rstV2, position) / area;
			const auto w1 = EdgeFunction(rstV2, rstV0, position) / area;
			const auto w2 = EdgeFunction(rstV0, rstV1, position) / area;

			if (w0 < 0.0f || w1 < 0.0f || w2 < 0.0f)
			{
				continue;
			}

			auto z = 1.0f / (1.0f / rstV0.z * w0 + 1.0f / rstV1.z * w1 + 1.0f / rstV2.z * w2);

			if (z < depthBuffer[y * 512 + x])
			{
				depthBuffer[y * 512 + x] = z;
				framebuffer.At(x, y) = z * (triangle[0].color / rstV0.z * w0 +
					                        triangle[1].color / rstV1.z * w1 +
					                        triangle[2].color / rstV2.z * w2);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	std::vector<Triangle> triangles;

	{
		auto triangle = Triangle
		{
			{ { -50.0f,  40.0f, 75.0f }, { 1.0f, 0.0f, 0.0f } },
			{ { -50.0f, -40.0f, 75.0f }, { 0.0f, 1.0f, 0.0f } },
			{ {  50.0f,   0.0f, 50.0f }, { 0.0f, 0.0f, 1.0f } }
		};

		triangles.push_back(triangle);
	}

	{
		auto triangle = Triangle
		{
			{ {  50.0f,  40.0f,  75.0f }, { 1.0f, 1.0f, 1.0f } },
			{ {  50.0f, -40.0f,  75.0f }, { 1.0f, 1.0f, 1.0f } },
			{ { -50.0f,   0.0f,  50.0f }, { 1.0f, 1.0f, 1.0f } }
		};

		triangles.push_back(triangle);
	}

	auto framebuffer = Framebuffer { glm::uvec2 { 512, 512 } };
	auto depthBuffer = std::vector<float>(512 * 512, std::numeric_limits<float>::max());

	for (auto& triangle : triangles)
	{
		DrawTriangle(triangle, framebuffer, depthBuffer);
	}

	framebuffer.Write("rasterization.bmp");

	return 0;
}