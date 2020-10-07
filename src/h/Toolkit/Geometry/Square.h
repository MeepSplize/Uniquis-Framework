#pragma once

#include "Toolkit\\Geometry\\IGeometry.h"

#include "Toolkit\\Geometry\\Point.h"

namespace Uniquis
{
	class Square : public IGeometry
	{
	public:

		Square();
		Square(float size);

	public:

		~Square();
	};
}