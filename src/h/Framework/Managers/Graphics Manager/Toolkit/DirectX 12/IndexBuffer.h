#pragma once

#include "Device.h"
#include "CommandList.h"
#include "Heap.h"
#include "Resource.h"

namespace Uniquis::DirectX12
{
	class IndexBuffer
	{
	private:

		std::shared_ptr<Heap<HeapType::Default>> pDefaultHeap;
		std::shared_ptr<Heap<HeapType::Upload>>  pUploadHeap;

	public:

		std::unique_ptr<Resource<ResourceType::Buffer>> pResource;
		std::unique_ptr<Resource<ResourceType::Buffer>> pUpload;

		std::vector<unsigned __int32> vIndices;

		IndexBufferDescriptor Descriptor;
	
	public:

		IndexBuffer(const std::vector<unsigned __int32> vIndices, 
					const CommandList&                  pCommandList, 
					const Device&                       pDevice);

		IndexBuffer(const unsigned __int64                                    defaultHeapOffset,
					const unsigned __int64                                    uploadHeapOffset,
					const	       std::vector<unsigned __int32>              vIndices, 
					const          std::shared_ptr<Heap<HeapType::Default>>& ppDefaultHeap,
					const          std::shared_ptr<Heap<HeapType::Upload>>&  ppUploadHeap,
					const          CommandList&                               pCommandList, 
					const          Device&                                    pDevice);

	public:

		~IndexBuffer();

	public:

		void update(const CommandList& pCommandList);

	public:

		ID3D12Resource* operator*() const;
	};
}