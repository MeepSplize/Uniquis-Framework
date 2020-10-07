#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\General\\Object.h"

Uniquis::Object::Object()

	: ModelID(0), MaterialID(0)
{
	
}

Uniquis::Object::Object(const unsigned __int32 modelID)

	: ModelID(modelID), MaterialID(0)
{
	
}

Uniquis::Object::Object(const unsigned __int32 modelID, const unsigned __int32 materialID)

	: ModelID(modelID), MaterialID(materialID)
{
	
}

Uniquis::Object::~Object()
{

}

void Uniquis::Object::bind(GraphicsManager& pGraphicsManager)
{
	pGraphicsManager.bind(this);
}

void Uniquis::Object::setModel(const unsigned __int32 modelID) noexcept
{
	this->ModelID = modelID;
}

void Uniquis::Object::setTransformation(const Uniquis::Transformation& pTransformation) noexcept
{
	this->Transformation = pTransformation;
}

void Uniquis::Object::move(const Vector<3>& pTranslation) noexcept
{
	this->Transformation.Translation += pTranslation;
}

void Uniquis::Object::rotate(const Vector<3>& pRotation) noexcept
{
	this->Transformation.Rotation += pRotation;
}

void Uniquis::Object::scale(const Vector<3>& pScale) noexcept
{
	this->Transformation.Scale += pScale;
}