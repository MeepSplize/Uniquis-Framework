#include "pch.h"

#include "Toolkit\\Geometry\\Point.h"

// CONSTRUCTORS

Uniquis::Point::Point()

	: Position(0.0f, 0.0f, 0.0f)
{

}

Uniquis::Point::Point(float positionX, float positionY, float positionZ)

	: Position(DirectX::XMFLOAT3(positionX, positionY, positionZ))
{

}

// DECONSTRUCTORS

Uniquis::Point::~Point()
{

}

// FUNCTIONS

// OPERATORS