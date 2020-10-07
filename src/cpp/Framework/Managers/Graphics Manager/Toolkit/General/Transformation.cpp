#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\General\\Transformation.h"

Uniquis::Transformation::Transformation()

	: Translation(),
	     Rotation(),
	        Scale()
{
	for (unsigned __int8 i = 0; i < 3; i++)
	{
		this->Scale.vComponents[i] = 1;
	}
}

Uniquis::Transformation::Transformation(const Vector<3>& pTranslation, const Vector<3>& pRotation, const Vector<3>& pScale)

	: Translation(pTranslation),
	     Rotation(pRotation),
	        Scale(pScale)
{

}

Uniquis::Transformation::~Transformation()
{

}

void Uniquis::Transformation::operator=(const Transformation& other) noexcept
{
	this->Translation = other.Translation;
	this->Rotation    = other.Rotation;
	this->Scale       = other.Scale;
}