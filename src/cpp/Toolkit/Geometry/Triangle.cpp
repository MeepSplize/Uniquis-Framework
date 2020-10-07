#include "pch.h"

#include "Toolkit\\Geometry\\Triangle.h"

// CONSTRUCTORS

Uniquis::Triangle::Triangle()
{
	this->vPoints.reserve(3);

	this->vPoints.emplace_back( 0.0f, 0.0f,  1.0f);
	this->vPoints.emplace_back( 1.0f, 0.0f, -1.0f);
	this->vPoints.emplace_back(-1.0f, 0.0f, -1.0f);
}

Uniquis::Triangle::Triangle(Point A, Point B, Point C)
{
	this->vPoints.push_back(A);
	this->vPoints.push_back(B);
	this->vPoints.push_back(C);
}

// DECONSTRUCTORS

Uniquis::Triangle::~Triangle()
{

}

// FUNCTIONS

// OPERATORS