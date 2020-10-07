#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\General\\Font.h"

Uniquis::Font::Font()
{

}

Uniquis::Font::~Font()
{

}

void Uniquis::Font::bind(GraphicsManager& pGraphicsManager)
{
	pGraphicsManager.bind(this);
}