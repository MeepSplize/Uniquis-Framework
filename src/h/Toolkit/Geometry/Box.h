#pragma once

#include "Toolkit\\Geometry\\IGeometry.h"

#include "Toolkit\\Geometry\\Point.h"

namespace Uniquis
{
	class Box : public IGeometry
	{

	// VARIABLES

	public:

	// CONSTRUCTORS

	public:

		Box();
		Box(float sizeX, float sizeY, float sizeZ);

	// DECONSTRUCTORS

	public:

		~Box();

	// FUNCTIONS

	public:

	// OPERATORS

	public:

	};
}