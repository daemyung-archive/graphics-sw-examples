
#include <iostream>
#include <random>

#include "image.h"
#include "sampler.h"

int main(int argc, char* argv[])
{
	auto source = Image { glm::uvec2 { 9, 9 } };

	for (auto y = uint32_t { 0 }; y != source.GetHeight(); ++y)
	{
		for (auto x = uint32_t { 0 }; x != source.GetWidth(); ++x)
		{
			auto randomGenerator = std::random_device {};

			const auto r = randomGenerator() % std::numeric_limits<uint8_t>::max();
			const auto g = randomGenerator() % std::numeric_limits<uint8_t>::max();
			const auto b = randomGenerator() % std::numeric_limits<uint8_t>::max();

			source.SetPixel(x, y, glm::vec4 { r, g, b, 255 });
		}
	}

	auto nearestDestination = Image   { glm::uvec2 { 256, 256 }      };
	auto nearestSampler     = Sampler { Sampler::FilterType::Nearest };

	for (auto y = uint32_t { 0 }; y != nearestDestination.GetHeight(); ++y)
	{
		for (auto x = uint32_t { 0 }; x != nearestDestination.GetWidth(); ++x)
		{
			const auto s = (x + 0.5f) / static_cast<float>(nearestDestination.GetWidth()  - 1);
			const auto t = (y + 0.5f) / static_cast<float>(nearestDestination.GetHeight() - 1);

			const auto pixel = nearestSampler.GetTexture(source, glm::vec2 { s, t });
			nearestDestination.SetPixel(x, y, pixel);
		}
	}

	nearestDestination.Write("nearest.bmp");

	auto linearDestination = Image   { glm::uvec2 { 256, 256 }     };
	auto linearSampler     = Sampler { Sampler::FilterType::Linear };

	for (auto y = uint32_t { 0 }; y != linearDestination.GetHeight(); ++y)
	{
		for (auto x = uint32_t { 0 }; x != linearDestination.GetWidth(); ++x)
		{
			const auto s = (x + 0.5f) / static_cast<float>(linearDestination.GetWidth()  - 1);
			const auto t = (y + 0.5f) / static_cast<float>(linearDestination.GetHeight() - 1);

			const auto pixel = linearSampler.GetTexture(source, glm::vec2 { s, t });
			linearDestination.SetPixel(x, y, pixel);
		}
	}

	linearDestination.Write("linear.bmp");

    auto cubicDestination = Image   { glm::uvec2 { 256, 256 }    };
	auto cubicSampler     = Sampler { Sampler::FilterType::Cubic };

	for (auto y = uint32_t { 0 }; y != cubicDestination.GetHeight(); ++y)
	{
		for (auto x = uint32_t { 0 }; x != cubicDestination.GetWidth(); ++x)
		{
			const auto s = (x + 0.5f) / static_cast<float>(cubicDestination.GetWidth()  - 1);
			const auto t = (y + 0.5f) / static_cast<float>(cubicDestination.GetHeight() - 1);

			const auto pixel = cubicSampler.GetTexture(source, glm::vec2 { s, t } );
            cubicDestination.SetPixel(x, y, pixel);
		}
	}

    cubicDestination.Write("cubic.bmp");

	return 0;
}