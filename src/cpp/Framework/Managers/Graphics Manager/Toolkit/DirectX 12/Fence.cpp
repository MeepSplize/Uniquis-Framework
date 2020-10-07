#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Fence.h"

Uniquis::DirectX12::Fence::Fence(const Device& device, const FenceFlags& flags)

	: FenceEvent(), ExpectedValue(0)
{
	HRESULT hResult;

	hResult = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&(this->pFence)));

	if (FAILED(hResult)) 
	{
		OutputDebugString(L"[ERROR] Fence Creation Failed \n");
	}

	this->FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	if (FenceEvent == nullptr) 
	{
		OutputDebugString(L"[ERROR] FenceEvent Creation Failed \n");
	}
}

Uniquis::DirectX12::Fence::~Fence()
{
	CloseHandle(this->FenceEvent);
}

void Uniquis::DirectX12::Fence::signal(UINT64 value)
{
	this->pFence->Signal(value);
}

bool Uniquis::DirectX12::Fence::completed() const
{
	if (this->pFence->GetCompletedValue() == this->ExpectedValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Uniquis::DirectX12::Fence::waitForCompletion()
{
	if (!(this->completed()))
	{
		HRESULT hResult;

		hResult = this->pFence->SetEventOnCompletion(this->ExpectedValue, this->FenceEvent);

		if (FAILED(hResult)) 
		{
			OutputDebugString(L"[ERROR] FenceEvent Couldn't Be Set \n");
		}

		WaitForSingleObject(this->FenceEvent, INFINITE);
	}
}

ID3D12Fence* Uniquis::DirectX12::Fence::operator*() const
{
	return this->pFence.Get();
}

UINT64& Uniquis::DirectX12::Fence::operator++()
{
	return ++(this->ExpectedValue);
}

UINT64 Uniquis::DirectX12::Fence::operator++(int)
{
	return this->ExpectedValue++;
}