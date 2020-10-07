#include "pch.h"

#include "Toolkit\\Geometry\\Rectangle.h"

// CONSTRUCTORS

Uniquis::Rectangle::Rectangle()
{
	this->vPoints.reserve(4);

	this->vPoints.emplace_back(-1.0f, 0.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f, 0.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f, 0.0f, -1.0f);
	this->vPoints.emplace_back(-1.0f, 0.0f, -1.0f);
}

Uniquis::Rectangle::Rectangle(float sizeX, float sizeZ)
{
	float SidedSizeX = (sizeX / 2);
	float SidedSizeZ = (sizeZ / 2);

	this->vPoints.reserve(4);

	this->vPoints.emplace_back(-(SidedSizeX), 0.0f,   SidedSizeZ);
	this->vPoints.emplace_back(  SidedSizeX,  0.0f,   SidedSizeZ);
	this->vPoints.emplace_back(  SidedSizeX,  0.0f, -(SidedSizeZ));
	this->vPoints.emplace_back(-(SidedSizeX), 0.0f, -(SidedSizeZ));
}

// DECONSTRUCTORS

Uniquis::Rectangle::~Rectangle()
{

}

// FUNCTIONS

// OPERATORS