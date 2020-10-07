#pragma once

#include "..\\Interfaces\\IDevice.h"

namespace Uniquis
{
	class Mouse
	{
	public:

		__int16 x;
		__int16 y;

	public:

		Mouse();

		~Mouse() = default;
	};
}