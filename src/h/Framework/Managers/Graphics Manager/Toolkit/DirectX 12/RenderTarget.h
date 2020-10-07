#pragma once

#include "Device.h"
#include "DescriptorHeap.h"
#include "Resource.h"

namespace Uniquis::DirectX12
{
	class RenderTarget
	{
	private:

		std::unique_ptr<Heap<HeapType::Default>>           pHeap;
		std::unique_ptr<Resource<ResourceType::Texture2D>> pResource;

	public:

		RenderTarget(const unsigned __int32                                                      width,
					 const unsigned __int32                                                      height,
			                        DescriptorHeap<DescriptorHeapType::RenderTargetDescriptors>& pDescriptorHeap,
					 const          Device&                                                      pDevice);

		~RenderTarget();
	};
}