#include "pch.h"

#include "Toolkit\\Geometry\\Line.h"

// CONSTRUCTORS

Uniquis::Line::Line()
{
	this->vPoints.reserve(2);

	this->vPoints.emplace_back(-1.0f, 0.0f, 0.0f);
	this->vPoints.emplace_back( 1.0f, 0.0f, 0.0f);
}

Uniquis::Line::Line(Point A, Point B)
{
	this->vPoints.push_back(A);
	this->vPoints.push_back(B);
}

// DECONSTRUCTORS

Uniquis::Line::~Line()
{

}

// FUNCTIONS

// OPERATORS