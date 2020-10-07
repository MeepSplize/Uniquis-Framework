#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\RenderTargetView.h"

RenderTargetView::RenderTargetView()

	: Handle()
{

}

RenderTargetView::~RenderTargetView()
{

}

void RenderTargetView::create(ID3D12Device* pDevice, Uniquis::DirectX12::SwapChain& SwapChain)
{
	HRESULT hResult;



	if (FAILED(hResult))
	{
		OutputDebugString(L"");
	}
}