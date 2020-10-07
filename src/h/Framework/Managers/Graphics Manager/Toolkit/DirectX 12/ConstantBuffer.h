#pragma once

#include "IBindable.h"

#include "CommandList.h"
#include "DescriptorHeap.h"
#include "Resource.h"

namespace Uniquis::DirectX12
{
	class ConstantBuffer
	{
	private:

		ConstantBufferDescriptorDescription DescriptorDescription;

		std::unique_ptr<Resource<ResourceType::Buffer>> pResource;
		std::unique_ptr<Resource<ResourceType::Buffer>> pUpload;

		std::shared_ptr<Heap<HeapType::Default>> pDefaultHeap;
		std::shared_ptr<Heap<HeapType::Upload>>  pUploadHeap;

	public:

		std::vector<float> vData;

	public:

		ConstantBuffer() = delete;

		ConstantBuffer(const ConstantBuffer&) = delete;

		ConstantBuffer(const ConstantBuffer&&) = delete;

		ConstantBuffer(const unsigned __int32                                                cConstants,
					                  DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
					   const          CommandList&                                           pCommandList,
					   const          Device&                                                pDevice);

		ConstantBuffer(const          std::vector<float>                                     vData, 
					                  DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
					   const          CommandList&                                           pCommandList, 
					   const          Device&                                                pDevice);

		~ConstantBuffer();

	public:

		void bind(const unsigned __int32                                                iPartition,
			                     DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			      const          Device&                                                pDevice);

		void update(const CommandList& pCommandList);
	};
}