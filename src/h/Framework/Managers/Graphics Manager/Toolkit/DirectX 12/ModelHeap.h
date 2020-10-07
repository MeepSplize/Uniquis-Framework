#pragma once

#include "Model.h"
#include "Device.h"
#include "Heap.h"
#include "DescriptorHeap.h"

namespace Uniquis::DirectX12
{
	class ModelHeap
	{
	private:

		std::shared_ptr<Heap<HeapType::Upload>>  pUploadHeap;
		std::shared_ptr<Heap<HeapType::Default>> pDefaultHeap;

	public:

		std::pair<unsigned __int64, unsigned __int64> ByteCapacity;

		DescriptorHeap<DescriptorHeapType::CommonDescriptors>* pDescriptorHeap;

		std::vector<unsigned __int16> vModelIDs;

		std::vector<std::unique_ptr<IndexBuffer>>  vpIndexBuffers;
		std::vector<std::unique_ptr<VertexBuffer>> vpVertexBuffers;

	public:

		ModelHeap() = delete;

		ModelHeap(const ModelHeap&) = delete;

		ModelHeap(const ModelHeap&&) = delete;

		ModelHeap(const unsigned __int64 heapByteSize,
				  const          Device& pDevice);

		~ModelHeap();

	public:

		void add(const std::wstring& pFilename,
				 const CommandList&  pCommandList,
				 const Device&       pDevice);

		void add(Model& pModel);

		void add(const unsigned __int32 modelID, std::vector<unsigned __int32> vIndices, std::vector<Vertex> vVertices, const CommandList& pCommandList, const Device& pDevice);
	};
}