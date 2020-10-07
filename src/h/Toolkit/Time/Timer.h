#pragma once

#include <Chrono>

namespace Uniquis
{
	class Timer
	{

	// VARIABLES

	private:

		std::chrono::steady_clock::time_point Timepoint;

	// CONSTRUCTORS

	public:

		Timer();

	// DECONSTRUCTORS

	public:

		~Timer();

	// FUNCTIONS

	public:

		void reset() noexcept;

		std::chrono::steady_clock::time_point getTimepoint() noexcept;

		std::chrono::duration<float> getDuration() noexcept;
	};
}