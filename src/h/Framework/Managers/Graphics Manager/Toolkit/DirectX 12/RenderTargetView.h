#pragma once

#include "WRL.h"

#include "DescriptorHeap.h"
#include "SwapChain.h"

class RenderTargetView
{
private:    /* --- Variables --- */

	D3D12_CPU_DESCRIPTOR_HANDLE Handle;

public:     /* --- Constructors --- */

	RenderTargetView();

public:     /* --- Deconstructors --- */

	~RenderTargetView();

public:     /* --- Functions --- */

	void create(ID3D12Device* pDevice, Uniquis::DirectX12::SwapChain& SwapChain);

public:     /* --- Operators --- */

	UINT8 operator*() const;
};