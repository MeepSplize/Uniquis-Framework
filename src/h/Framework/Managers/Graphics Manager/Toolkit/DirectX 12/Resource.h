#pragma once

#include "Flags.h"
#include "Types.h"

#include "Device.h"
#include "Heap.h"

#include "ResourceDescription.h"

namespace Uniquis::DirectX12
{
	template<ResourceType Type>
	class Resource
	{
	private:

		ID3D12Resource* pResource;

	public:

		InternalResourceBarrier Barrier;

	public:

		Resource(const unsigned __int64                                   heapOffset,
				                Uniquis::DirectX12::ResourceDescription<Type>& description,
				 const          Uniquis::DirectX12::Heap<HeapType::Default>&  heap,
				 const          Uniquis::DirectX12::Device&                    device);

		Resource(const unsigned __int64                                   heapOffset,
				                Uniquis::DirectX12::ResourceDescription<Type>& description,
				 const          Uniquis::DirectX12::Heap<HeapType::Upload>&   heap,
				 const          Uniquis::DirectX12::Device&                    device);

		~Resource();

	public:

		ID3D12Resource* operator*()  const noexcept;
		ID3D12Resource* operator->() const noexcept;
	};
}