#include "pch.h"

#include "Toolkit\\Geometry\\Box.h"

// CONSTRUCTORS

Uniquis::Box::Box()
{
	this->vPoints.reserve(8);

	this->vPoints.emplace_back(-1.0f,  1.0f, -1.0f);
	this->vPoints.emplace_back( 1.0f,  1.0f, -1.0f);
	this->vPoints.emplace_back( 1.0f, -1.0f, -1.0f);
	this->vPoints.emplace_back(-1.0f, -1.0f, -1.0f);
	this->vPoints.emplace_back(-1.0f,  1.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f,  1.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f, -1.0f,  1.0f);
	this->vPoints.emplace_back(-1.0f, -1.0f,  1.0f);
}

Uniquis::Box::Box(float sizeX, float sizeY, float sizeZ)
{
	float SidedSizeX = (sizeX / 2);
	float SidedSizeY = (sizeY / 2);
	float SidedSizeZ = (sizeZ / 2);

	this->vPoints.reserve(8);

	this->vPoints.emplace_back(-(SidedSizeX),   SidedSizeY,  -(SidedSizeZ));
	this->vPoints.emplace_back(  SidedSizeX,    SidedSizeY,  -(SidedSizeZ));
	this->vPoints.emplace_back(  SidedSizeX,  -(SidedSizeY), -(SidedSizeZ));
	this->vPoints.emplace_back(-(SidedSizeX), -(SidedSizeY), -(SidedSizeZ));
	this->vPoints.emplace_back(-(SidedSizeX),   SidedSizeY,    SidedSizeZ);
	this->vPoints.emplace_back(  SidedSizeX,    SidedSizeY,    SidedSizeZ);
	this->vPoints.emplace_back(  SidedSizeX,  -(SidedSizeY),   SidedSizeZ);
	this->vPoints.emplace_back(-(SidedSizeX), -(SidedSizeY),   SidedSizeZ);
}

// DECONSTRUCTORS

Uniquis::Box::~Box()
{

}

// FUNCTIONS

// OPERATORS