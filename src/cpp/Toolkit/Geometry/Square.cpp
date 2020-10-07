#include "pch.h"

#include "Toolkit\\Geometry\\Square.h"

// CONSTRUCTORS

Uniquis::Square::Square()
{
	this->vPoints.reserve(4);

	this->vPoints.emplace_back(-1.0f, 0.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f, 0.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f, 0.0f, -1.0f);
	this->vPoints.emplace_back(-1.0f, 0.0f, -1.0f);
}

Uniquis::Square::Square(float size)
{
	float SidedSize = (size / 2);

	this->vPoints.reserve(4);

	this->vPoints.emplace_back(-(SidedSize), 0.0f,   SidedSize);
	this->vPoints.emplace_back(  SidedSize,  0.0f,   SidedSize);
	this->vPoints.emplace_back(  SidedSize,  0.0f, -(SidedSize));
	this->vPoints.emplace_back(-(SidedSize), 0.0f, -(SidedSize));
}

// DECONSTRUCTORS

Uniquis::Square::~Square()
{

}

// FUNCTIONS

// OPERATORS