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

#ifndef __BOX_H__
#define __BOX_H__

#include <cstdint>

class Box
{
public:
	Box(int32_t top, int32_t left, int32_t bottom, int32_t right);

	void Clamp(int32_t top, int32_t left, int32_t bottom, int32_t right);

	auto GetTop() const
	{
		return mTop;
	}

	auto GetLeft() const
	{
		return mLeft;
	}

	auto GetBottom() const
	{
		return mBottom;
	}

	auto GetRight() const
	{
		return mRight;
	}

private:
	int32_t mTop;
	int32_t mLeft;
	int32_t mBottom;
	int32_t mRight;
};

#endif