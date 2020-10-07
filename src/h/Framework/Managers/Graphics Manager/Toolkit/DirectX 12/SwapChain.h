#pragma once

#include <WRL.h>

#include "Flags.h"

#include "Factory.h"
#include "Device.h"
#include "CommandQueue.h"
#include "CommandAllocator.h"
#include "DescriptorHeap.h"
#include "Viewport.h"
#include "ScissorRect.h"
#include "ModeDesc.h"
#include "SampleDescription.h"
#include "FullscreenDesc.h"

namespace Uniquis::DirectX12 
{
	class SwapChain 
	{
	private:

		Microsoft::WRL::ComPtr<IDXGISwapChain3> pSwapChain;

		DXGI_SWAP_CHAIN_DESC1 SwapChainDescStruct;

	public:

		unsigned __int16 Width;
		unsigned __int16 Height;

		UINT8 iBuffer;
		UINT8 cBuffers;

		std::vector<CommandAllocator>   vCommandAllocators;
		std::unique_ptr<DescriptorHeap<DescriptorHeapType::RenderTargetDescriptors>> pRTVDescriptorHeap;

		Viewport       Viewport;
		ScissorRect    ScissorRect;

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> vpRenderTargets;

	public:

		SwapChain(const unsigned __int16		 width,
				  const unsigned __int16		 height,
				  const			 HWND&			 hWnd, 
				  const			 Factory&		 factory, 
				  const			 Device&		 device,
				  const			 CommandQueue&	 commandQueue, 
				  const			 SwapChainFlags& flags);

		~SwapChain();

	public:

		void present(const __int8 syncInterval);

	public:

		IDXGISwapChain3* operator->() const noexcept;
	};
}