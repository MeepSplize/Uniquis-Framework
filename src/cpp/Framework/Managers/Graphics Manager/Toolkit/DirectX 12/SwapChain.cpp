#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\SwapChain.h"

Uniquis::DirectX12::SwapChain::SwapChain(const unsigned __int16		   width,
									const unsigned __int16		   height,
									const		   HWND&		   hWnd,
									const		   Factory&		   factory,
									const		   Device&		   device,
									const		   CommandQueue&   commandQueue,
									const		   SwapChainFlags& flags)

	: SwapChainDescStruct(),
	   pRTVDescriptorHeap(),
	             cBuffers(0),
	              iBuffer(0),
					Width(width),
				   Height(height)
{
	using namespace Microsoft::WRL;

	HRESULT hResult;

	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS SampleInformation = {};

	SampleInformation.Format      = DXGI_FORMAT_R8G8B8A8_UNORM;
	SampleInformation.SampleCount = 1;

	device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &(SampleInformation), sizeof(SampleInformation));

	switch (flags)
	{
		case SwapChainFlags::NONE:
		{
			this->SwapChainDescStruct.Width		  = width;
			this->SwapChainDescStruct.Height	  = height;
			this->SwapChainDescStruct.Format	  = DXGI_FORMAT_R8G8B8A8_UNORM;
			this->SwapChainDescStruct.Stereo	  = false;
			this->SwapChainDescStruct.SampleDesc  = **(SampleDescription(SampleInformation.SampleCount, (SampleInformation.NumQualityLevels - 1)));
			this->SwapChainDescStruct.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			this->SwapChainDescStruct.BufferCount = 3;
			this->SwapChainDescStruct.Scaling	  = DXGI_SCALING_NONE;
			this->SwapChainDescStruct.SwapEffect  = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			this->SwapChainDescStruct.AlphaMode	  = DXGI_ALPHA_MODE_UNSPECIFIED;
			this->SwapChainDescStruct.Flags		  = 0;
		}
	}

	this->cBuffers = this->SwapChainDescStruct.BufferCount;

	ComPtr<IDXGISwapChain1> pTempSwapChain;

	hResult = factory->CreateSwapChainForHwnd(*(commandQueue),
											  hWnd,
											  &(this->SwapChainDescStruct),
											  &(*(FullscreenDesc(flags))),
											  0,               // Change later to restrict to Monitor
											  &(pTempSwapChain));

	if (FAILED(hResult))
	{
		OutputDebugString(L"[ERROR] Failed to create Swap Chain! \n");

		_com_error ComError(hResult);
		
		LPCTSTR ComErrorMessage = ComError.ErrorMessage();

		OutputDebugString(std::wstring(L"HRESULT: ").append(ComErrorMessage).append(L"\n").c_str());
	}

	pTempSwapChain.As(&(this->pSwapChain));

	this->iBuffer = this->pSwapChain->GetCurrentBackBufferIndex();

	// RENDERTARGETS
	
	DescriptorHeapDescription RTVDescriptorHeapDescription(this->cBuffers, DescriptorHeapFlags::NONE);

	this->pRTVDescriptorHeap = std::make_unique<DescriptorHeap<DescriptorHeapType::RenderTargetDescriptors>>(RTVDescriptorHeapDescription, device);

	D3D12_CPU_DESCRIPTOR_HANDLE hRTV = this->pRTVDescriptorHeap->CPUHandle;

	this->vpRenderTargets.reserve(this->cBuffers);

	this->vCommandAllocators.reserve(this->cBuffers);

	for (__int8 i = 0; i < this->cBuffers; i++)
	{
		this->vpRenderTargets.emplace_back();

		this->vCommandAllocators.emplace_back(device, CommandAllocatorFlags::NONE);

		hResult = this->pSwapChain->GetBuffer(i, IID_PPV_ARGS(&(vpRenderTargets[i])));

		if (FAILED(hResult))
		{
			OutputDebugString(L"[ERROR] !!!!!!!! \n");
		}

		device->CreateRenderTargetView(this->vpRenderTargets[i].Get(), nullptr, hRTV);

		hRTV.ptr += this->pRTVDescriptorHeap->IncrementSize;
	}

	// VIEWPORT / SCISSORRECT

	this->Viewport->Width  = width;
	this->Viewport->Height = height;

	this->ScissorRect->right  = width;
	this->ScissorRect->bottom = height;
}

Uniquis::DirectX12::SwapChain::~SwapChain()
{

}

void Uniquis::DirectX12::SwapChain::present(const __int8 syncInterval)
{
	HRESULT hResult;

	if (FAILED(this->pSwapChain->Present(syncInterval, 0)))
	{
		OutputDebugString(L"[ERROR] Failed to present SwapChain \n");
	}
}

IDXGISwapChain3* Uniquis::DirectX12::SwapChain::operator->() const noexcept
{
	return this->pSwapChain.Get();
}