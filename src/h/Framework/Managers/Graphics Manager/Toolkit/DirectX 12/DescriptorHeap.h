#pragma once

#include "Toolkit\\Memory\\PartitionDescriptor.h"

#include "Flags.h"

#include "Device.h"
#include "DescriptorHeapDescription.h"

namespace Uniquis::DirectX12
{
	enum class DescriptorHeapType
	{
		CommonDescriptors,
		DepthStencilDescriptors,
		RenderTargetDescriptors,
		SamplerDescriptors
	};

	template<DescriptorHeapType Type>
	class DescriptorHeap
	{
	private:

		ID3D12DescriptorHeap* pDescriptorHeap;

	public:

		unsigned __int32 IncrementSize;

		std::vector<PartitionDescriptor> vPartitionDescriptors;

		D3D12_CPU_DESCRIPTOR_HANDLE CPUHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE GPUHandle;

	public:

		DescriptorHeap(DescriptorHeapDescription& pDescription, const Device& pDevice);

		~DescriptorHeap();

	public:

		D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandleToDescriptor(const unsigned __int32 index) noexcept;
		D3D12_GPU_DESCRIPTOR_HANDLE getGPUHandleToDescriptor(const unsigned __int32 index) noexcept;

		unsigned __int32 addDescriptor(unsigned __int16 iPartition, ConstantBufferDescriptorDescription& description, const Device& pDevice);

	public:

		ID3D12DescriptorHeap* operator*()  const noexcept;
		ID3D12DescriptorHeap* operator->() const noexcept;
	};
}