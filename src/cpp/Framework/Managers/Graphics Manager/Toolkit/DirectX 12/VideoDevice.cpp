#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\VideoDevice.h"

Uniquis::DirectX12::VideoDevice::VideoDevice(const Device& pDevice)
{
	pDevice->QueryInterface(__uuidof(ID3D12VideoDevice), reinterpret_cast<void**>(&(this->pInternal)));
}

Uniquis::DirectX12::VideoDevice::~VideoDevice()
{
	this->pInternal->Release();
}

ID3D12VideoDevice1* Uniquis::DirectX12::VideoDevice::operator*() const
{
	return this->pInternal;
}

ID3D12VideoDevice1* Uniquis::DirectX12::VideoDevice::operator->() const
{
	return this->pInternal;
}