#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Factory.h"

Uniquis::DirectX12::Factory::Factory(const FactoryFlag& pFlags)
{
	if (FAILED(CreateDXGIFactory2(static_cast<std::underlying_type<FactoryFlag>::type>(pFlags), IID_PPV_ARGS(&(this->pFactory)))))
	{
		OutputDebugString(L"[ERROR] Factory Creation Failed! \n");
	}
}

Uniquis::DirectX12::Factory::~Factory()
{
	this->pFactory->Release();
}

IDXGIFactory7* Uniquis::DirectX12::Factory::operator*() const noexcept
{
	return this->pFactory;
}

IDXGIFactory7* Uniquis::DirectX12::Factory::operator->() const noexcept
{
	return this->pFactory;
}