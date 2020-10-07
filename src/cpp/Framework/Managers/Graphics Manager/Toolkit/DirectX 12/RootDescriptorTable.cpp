#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\RootDescriptorTable.h"

Uniquis::DirectX12::RootDescriptorTable::RootDescriptorTable(const unsigned __int32*                                        vcDescriptorRanges, 
														     const DescriptorRange<DescriptorRangeType::ShaderResources>*   pShaderResourceDescriptorRanges,
														     const DescriptorRange<DescriptorRangeType::UnorderedAccesses>* pUnorderedAccessDescriptorRanges,
														     const DescriptorRange<DescriptorRangeType::ConstantBuffers>*   pConstantBufferDescriptorRanges,
														     const DescriptorRange<DescriptorRangeType::Samplers>*          pSamplerDescriptorRanges)
{
	for (unsigned __int32 i = 0; i < vcDescriptorRanges[0]; i++)
	{
		this->vInternalDescriptorRanges.push_back(**(pShaderResourceDescriptorRanges));

		this->vInternalDescriptorRanges[this->vInternalDescriptorRanges.size() - 1].OffsetInDescriptorsFromTableStart = (this->vInternalDescriptorRanges.size() - 1);
	}

	for (unsigned __int32 i = 0; i < vcDescriptorRanges[1]; i++)
	{
		this->vInternalDescriptorRanges.push_back(**(pUnorderedAccessDescriptorRanges));

		this->vInternalDescriptorRanges[this->vInternalDescriptorRanges.size() - 1].OffsetInDescriptorsFromTableStart = (this->vInternalDescriptorRanges.size() - 1);
	}

	for (unsigned __int32 i = 0; i < vcDescriptorRanges[2]; i++)
	{
		this->vInternalDescriptorRanges.push_back(**(pConstantBufferDescriptorRanges));

		this->vInternalDescriptorRanges[this->vInternalDescriptorRanges.size() - 1].OffsetInDescriptorsFromTableStart = (this->vInternalDescriptorRanges.size() - 1);
	}

	for (unsigned __int32 i = 0; i < vcDescriptorRanges[3]; i++)
	{
		this->vInternalDescriptorRanges.push_back(**(pSamplerDescriptorRanges));

		this->vInternalDescriptorRanges[this->vInternalDescriptorRanges.size() - 1].OffsetInDescriptorsFromTableStart = (this->vInternalDescriptorRanges.size() - 1);
	}

	this->InternalClass.NumDescriptorRanges = this->vInternalDescriptorRanges.size();

	this->InternalClass.pDescriptorRanges = this->vInternalDescriptorRanges.data();
}

Uniquis::DirectX12::RootDescriptorTable::RootDescriptorTable(const std::initializer_list<unsigned __int32>&                 vcDescriptorRanges,
														const DescriptorRange<DescriptorRangeType::ShaderResources>*   pShaderResourceDescriptorRanges,
														const DescriptorRange<DescriptorRangeType::UnorderedAccesses>* pUnorderedAccessDescriptorRanges,
														const DescriptorRange<DescriptorRangeType::ConstantBuffers>*   pConstantBufferDescriptorRanges,
														const DescriptorRange<DescriptorRangeType::Samplers>*          pSamplerDescriptorRanges)
{
	for (unsigned __int32 i = 0; i < vcDescriptorRanges.begin()[0]; i++)
	{
		this->vInternalDescriptorRanges.push_back(**(pShaderResourceDescriptorRanges));

		this->vInternalDescriptorRanges[this->vInternalDescriptorRanges.size() - 1].OffsetInDescriptorsFromTableStart = (this->vInternalDescriptorRanges.size() - 1);
	}

	for (unsigned __int32 i = 0; i < vcDescriptorRanges.begin()[1]; i++)
	{
		this->vInternalDescriptorRanges.push_back(**(pUnorderedAccessDescriptorRanges));

		this->vInternalDescriptorRanges[this->vInternalDescriptorRanges.size() - 1].OffsetInDescriptorsFromTableStart = (this->vInternalDescriptorRanges.size() - 1);
	}

	for (unsigned __int32 i = 0; i < vcDescriptorRanges.begin()[2]; i++)
	{
		this->vInternalDescriptorRanges.push_back(**(pConstantBufferDescriptorRanges));

		this->vInternalDescriptorRanges[this->vInternalDescriptorRanges.size() - 1].OffsetInDescriptorsFromTableStart = (this->vInternalDescriptorRanges.size() - 1);
	}

	for (unsigned __int32 i = 0; i < vcDescriptorRanges.begin()[3]; i++)
	{
		this->vInternalDescriptorRanges.push_back(**(pSamplerDescriptorRanges));

		this->vInternalDescriptorRanges[this->vInternalDescriptorRanges.size() - 1].OffsetInDescriptorsFromTableStart = (this->vInternalDescriptorRanges.size() - 1);
	}

	this->InternalClass.NumDescriptorRanges = this->vInternalDescriptorRanges.size();

	this->InternalClass.pDescriptorRanges = this->vInternalDescriptorRanges.data();
}

Uniquis::DirectX12::RootDescriptorTable::~RootDescriptorTable()
{

}

const D3D12_ROOT_DESCRIPTOR_TABLE1& Uniquis::DirectX12::RootDescriptorTable::operator*() const
{
	return this->InternalClass;
}