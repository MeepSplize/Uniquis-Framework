#pragma once

#include "Device.h"
#include "CommandList.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Heap.h"
#include "Resource.h"

namespace Uniquis::DirectX12
{
	class BottomLevelAccelerationStructure
	{
	public:

		std::unique_ptr<Heap<HeapType::Default>> pHeap;

		std::unique_ptr<Resource<ResourceType::Buffer>> pScratchResource;
		std::unique_ptr<Resource<ResourceType::Buffer>> pInternalStructureResource;

	public:

		BottomLevelAccelerationStructure(const IndexBuffer&  pIndexBuffer, 
										 const VertexBuffer& pVertexBuffer, 
										 const CommandList&  pCommandList, 
										 const Device&       pDevice);

		~BottomLevelAccelerationStructure();
	};
}