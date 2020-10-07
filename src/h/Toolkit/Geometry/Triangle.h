#pragma once

#include "Toolkit\\Geometry\\IGeometry.h"

#include "Toolkit\\Geometry\\Point.h"

namespace Uniquis
{
	class Triangle : public IGeometry
	{

	// VARIABLES

	public:

	// CONSTRUCTORS

	public:

		Triangle();
		Triangle(Point A, Point B, Point C);

	// DECONSTRUCTORS

	public:

		~Triangle();

	// FUNCTIONS

	public:

	// OPERATORS

	public:

	};
}