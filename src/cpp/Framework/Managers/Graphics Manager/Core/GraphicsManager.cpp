#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Core\\GraphicsManager.h"

Uniquis::GraphicsManager::GraphicsManager()
{
#if   WINDOWS_VERSION == 7

	this->pGraphicsAPI = std::make_unique<Uniquis::D3D11::D3D11>();

#elif WINDOWS_VERSION == 10

	this->pGraphicsAPI = std::make_unique<Uniquis::DirectX12::DirectX12>();

#endif
}

Uniquis::GraphicsManager::~GraphicsManager()
{

}

Uniquis::GraphicsManager& Uniquis::GraphicsManager::getReference()
{
	static GraphicsManager Instance;

	return Instance;
}

void Uniquis::GraphicsManager::addWindow(const unsigned __int16 width, const unsigned __int16 height, HWND hWindow)
{
	this->pGraphicsAPI->addWindow(width, height, hWindow);
}

void Uniquis::GraphicsManager::render(const float time, const unsigned __int8 windowIndex) const
{
	this->pGraphicsAPI->render(time, windowIndex);
}

void Uniquis::GraphicsManager::bind(Font* pFont)
{
	this->pGraphicsAPI->bind(pFont);
}

void Uniquis::GraphicsManager::bind(Text* pText)
{
	this->pGraphicsAPI->bind(pText);
}

void Uniquis::GraphicsManager::bind(Object* pObject)
{
	this->pGraphicsAPI->bind(pObject);
}

void Uniquis::GraphicsManager::release()
{
	this->pGraphicsAPI->release();
}