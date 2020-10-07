#pragma once

#include "..\\Interfaces\\IDevice.h"

namespace Uniquis
{
	class Keyboard
	{
	public:

		std::array<bool, 42> bKeys;

		Keyboard(Keyboard&& other) noexcept;

		Keyboard();

		~Keyboard() = default;
	};
}