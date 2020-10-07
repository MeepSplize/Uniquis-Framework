#pragma once

#include "Device.h"
#include "CommandList.h"
#include "Heap.h"
#include "DescriptorHeap.h"
#include "Resource.h"

namespace Uniquis::DirectX12
{
	class DepthBuffer
	{
	private:

		std::unique_ptr<Heap<HeapType::Default>>          pHeap;
		std::unique_ptr<Resource<ResourceType::Texture2D>> pResource;

		D3D12_CPU_DESCRIPTOR_HANDLE Handle;

	public:

		DepthBuffer(const unsigned __int32                                                      width,
					const unsigned __int32                                                      height,
					               DescriptorHeap<DescriptorHeapType::DepthStencilDescriptors>& pDescriptorHeap,
					const          Device&                                                      pDevice);

	public:

		~DepthBuffer();

	public:

		void clear(const CommandList& pCommandList);

	public:

		D3D12_CPU_DESCRIPTOR_HANDLE* operator*() noexcept;
	};
}