#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\CommandAllocator.h"

Uniquis::DirectX12::CommandAllocator::CommandAllocator(const Device& device, const CommandAllocatorFlags& flags)
{
	HRESULT hResult;

	hResult = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&(this->pCommandAllocator)));

	if (FAILED(hResult))
	{
		OutputDebugString(L"[ERROR] !!!!!!!! \n");
	}
}

Uniquis::DirectX12::CommandAllocator::~CommandAllocator()
{

}

void Uniquis::DirectX12::CommandAllocator::reset()
{
	HRESULT hResult;

	hResult = this->pCommandAllocator->Reset();

	if (FAILED(hResult))
	{
		OutputDebugString(L"[ERROR] Failed to reset CommandAllocator");
	}
}

ID3D12CommandAllocator* Uniquis::DirectX12::CommandAllocator::operator*() const noexcept
{
	return this->pCommandAllocator.Get();
}

ID3D12CommandAllocator* Uniquis::DirectX12::CommandAllocator::operator->() const noexcept
{
	return this->pCommandAllocator.Get();
}