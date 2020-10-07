#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\DebugController.h"

Uniquis::DirectX12::DebugController::DebugController()
{
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&(this->pDebug)))))
	{
		this->pDebug->EnableDebugLayer();
	}
}

Uniquis::DirectX12::DebugController::~DebugController()
{
	this->pDebug->Release();
}

ID3D12Debug* Uniquis::DirectX12::DebugController::operator*() const noexcept
{
	return this->pDebug;
}

ID3D12Debug* Uniquis::DirectX12::DebugController::operator->() const noexcept
{
	return this->pDebug;
}
