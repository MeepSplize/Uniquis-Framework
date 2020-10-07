#include "pch.h"

#include "Toolkit\\Geometry\\Cube.h"

// CONSTRUCTORS

Uniquis::Cube::Cube()
{
	this->vPoints.reserve(8);

	this->vPoints.emplace_back(-1.0f, -1.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f, -1.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f, -1.0f, -1.0f);
	this->vPoints.emplace_back(-1.0f, -1.0f, -1.0f);
	this->vPoints.emplace_back(-1.0f,  1.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f,  1.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f,  1.0f, -1.0f);
	this->vPoints.emplace_back(-1.0f,  1.0f, -1.0f);
}

Uniquis::Cube::Cube(float size)
{										    
	float SidedSize = (size / 2);

	this->vPoints.reserve(8);

	this->vPoints.emplace_back(-(SidedSize), -(SidedSize),   SidedSize);
	this->vPoints.emplace_back(  SidedSize,  -(SidedSize),   SidedSize);
	this->vPoints.emplace_back(  SidedSize,  -(SidedSize), -(SidedSize));
	this->vPoints.emplace_back(-(SidedSize), -(SidedSize), -(SidedSize));
	this->vPoints.emplace_back(-(SidedSize),   SidedSize,    SidedSize);
	this->vPoints.emplace_back(  SidedSize,    SidedSize,    SidedSize);
	this->vPoints.emplace_back(  SidedSize,    SidedSize,  -(SidedSize));
	this->vPoints.emplace_back(-(SidedSize),   SidedSize,  -(SidedSize));
}

// DECONSTRUCTORS

Uniquis::Cube::~Cube()
{

}

// FUNCTIONS

// OPERATORS