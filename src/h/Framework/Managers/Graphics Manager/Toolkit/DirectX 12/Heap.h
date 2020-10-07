#pragma once

#include "Flags.h"
#include "Types.h"

#include "Device.h"

#include "HeapDescription.h"

namespace Uniquis::DirectX12
{
	template<HeapType Type>
	class Heap
	{
	private:

		ID3D12Heap* pHeap;

	public:

		std::pair<unsigned __int64, unsigned __int64> ByteCapacity;

	public:

		Heap(HeapDescription<Type>& pDescription, const Device& pDevice);

		~Heap();

	public:

		ID3D12Heap* operator*()  const noexcept;
		ID3D12Heap* operator->() const noexcept;

		
	};
}