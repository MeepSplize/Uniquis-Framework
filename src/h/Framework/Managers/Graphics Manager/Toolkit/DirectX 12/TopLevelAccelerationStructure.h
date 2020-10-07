#pragma once

#include "Device.h"
#include "CommandList.h"
#include "BottomLevelAccelerationStructure.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Heap.h"
#include "Resource.h"

namespace Uniquis::DirectX12
{
	class TopLevelAccelerationStructure
	{
	public:

		std::unique_ptr<Heap<HeapType::Default>> pDefaultHeap;
		std::unique_ptr<Heap<HeapType::Upload>>  pUploadHeap;

		std::unique_ptr<Resource<ResourceType::Buffer>> pScratchResource;
		std::unique_ptr<Resource<ResourceType::Buffer>> pInternalStructureResource;
		std::unique_ptr<Resource<ResourceType::Buffer>> pInstanceDescriptionsResource;

	public:

		TopLevelAccelerationStructure(const BottomLevelAccelerationStructure* pBottomLevelAccelerationStructure,
									  const CommandList&                      pCommandList, 
									  const Device&                           pDevice);

		~TopLevelAccelerationStructure();
	};
}