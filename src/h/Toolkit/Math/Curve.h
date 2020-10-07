#pragma once

#include "Vector.h"

namespace Uniquis
{
	template<unsigned __int8 Dimension>
	class Curve
	{
	public:

		std::array<Vector<Dimension>, 2> vAnchorPoints;
		std::array<Vector<Dimension>, 2> vControlPoints;

	public:

		Curve();

		~Curve();

	public:

		Vector<Dimension> interpolate(const float interpolation);

	public:

		void operator=(const Curve&) = delete;
	};
}