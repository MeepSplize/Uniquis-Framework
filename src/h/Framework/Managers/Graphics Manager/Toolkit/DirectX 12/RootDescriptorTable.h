#pragma once

#include "DescriptorRange.h"

namespace Uniquis::DirectX12
{
	class RootDescriptorTable
	{
	public:

		D3D12_ROOT_DESCRIPTOR_TABLE1 InternalClass;

		std::vector<D3D12_DESCRIPTOR_RANGE1> vInternalDescriptorRanges;

	public:

		RootDescriptorTable() = delete;

		RootDescriptorTable(const RootDescriptorTable&) = delete;

		RootDescriptorTable(const RootDescriptorTable&&) = delete;

		RootDescriptorTable(const unsigned __int32*                                        vcDescriptorRanges, 
							const DescriptorRange<DescriptorRangeType::ShaderResources>*   pShaderResourceDescriptorRanges,
							const DescriptorRange<DescriptorRangeType::UnorderedAccesses>* pUnorderedAccessDescriptorRanges,
							const DescriptorRange<DescriptorRangeType::ConstantBuffers>*   pConstantBufferDescriptorRanges,
							const DescriptorRange<DescriptorRangeType::Samplers>*          pSamplerDescriptorRanges);

		RootDescriptorTable(const std::initializer_list<unsigned __int32>&                 vcDescriptorRanges, 
							const DescriptorRange<DescriptorRangeType::ShaderResources>*   pShaderResourceDescriptorRanges,
							const DescriptorRange<DescriptorRangeType::UnorderedAccesses>* pUnorderedAccessDescriptorRanges,
							const DescriptorRange<DescriptorRangeType::ConstantBuffers>*   pConstantBufferDescriptorRanges,
							const DescriptorRange<DescriptorRangeType::Samplers>*          pSamplerDescriptorRanges);

		~RootDescriptorTable();

	public:

		void operator=(const RootDescriptorTable&) = delete;

		const D3D12_ROOT_DESCRIPTOR_TABLE1& operator*() const;
	};
}