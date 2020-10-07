#pragma once

#include "Device.h"
#include "CommandList.h"
#include "Heap.h"
#include "Resource.h"
#include "Vertex.h"

namespace Uniquis::DirectX12
{
	class VertexBuffer
	{
	private:

		std::shared_ptr<Heap<HeapType::Default>> pDefaultHeap;
		std::shared_ptr<Heap<HeapType::Upload>>  pUploadHeap;

	public:

		std::unique_ptr<Resource<ResourceType::Buffer>> pResource;
		std::unique_ptr<Resource<ResourceType::Buffer>> pUpload;

		std::vector<Vertex> vVertices;

		VertexBufferDescriptor Descriptor;
		
	public:

		VertexBuffer(const std::vector<Vertex> vVertices, 
					 const CommandList&        pCommandList, 
					 const Device&             pDevice);

		VertexBuffer(const unsigned __int64                                   defaultHeapOffset,
					 const unsigned __int64                                   uploadHeapOffset,
					 const          std::vector<Vertex>                       vVertices, 
					 const          std::shared_ptr<Heap<HeapType::Default>>& ppDefaultHeap,
					 const          std::shared_ptr<Heap<HeapType::Upload>>&  ppUploadHeap,
					 const          CommandList&                              pCommandList, 
					 const          Device&                                   pDevice);

	public:

		~VertexBuffer();

	public:

		void update(const CommandList& pCommandList);

	public:

		ID3D12Resource* operator*() const noexcept;
	};
}