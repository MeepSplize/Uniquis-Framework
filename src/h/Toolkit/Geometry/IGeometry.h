#pragma once

#include "Toolkit\\Geometry\\Point.h"

namespace Uniquis
{
	class IGeometry
	{
	public:

		std::vector<Point> vPoints;

	public:

		IGeometry();

		virtual ~IGeometry() = 0;
	};
}