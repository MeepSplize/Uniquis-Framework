#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\General\\Text.h"

Uniquis::Text::Text()
{

}

Uniquis::Text::Text(const std::wstring& pString)

	: iFont(0), String(pString)
{
	
}

Uniquis::Text::Text(const unsigned __int16 iFont, const std::wstring& pString)

	: iFont(iFont), String(pString)
{
	
}

Uniquis::Text::~Text()
{

}

void Uniquis::Text::bind(GraphicsManager& pGraphicsManager)
{
	pGraphicsManager.bind(this);
}

void Uniquis::Text::set(const std::wstring& pString)
{
	this->String = pString;
}