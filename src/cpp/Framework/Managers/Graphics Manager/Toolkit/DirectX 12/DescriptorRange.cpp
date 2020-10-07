#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\DescriptorRange.h"

template<Uniquis::DirectX12::DescriptorRangeType Type>
Uniquis::DirectX12::DescriptorRange<Type>::DescriptorRange(const unsigned __int16 shaderRegisterStart, const unsigned __int16 shaderRegisterEnd)

	: InternalClass()
{

}

template<>
Uniquis::DirectX12::DescriptorRange<Uniquis::DirectX12::DescriptorRangeType::ShaderResources>::DescriptorRange(const unsigned __int16 shaderRegisterStart, const unsigned __int16 shaderRegisterEnd)

	: InternalClass()
{
	this->InternalClass.RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	this->InternalClass.NumDescriptors     = (shaderRegisterEnd - shaderRegisterStart + 1);
	this->InternalClass.BaseShaderRegister = shaderRegisterStart;
	this->InternalClass.RegisterSpace      = 0;
	this->InternalClass.Flags              = D3D12_DESCRIPTOR_RANGE_FLAG_NONE;
}

template<>
Uniquis::DirectX12::DescriptorRange<Uniquis::DirectX12::DescriptorRangeType::UnorderedAccesses>::DescriptorRange(const unsigned __int16 shaderRegisterStart, const unsigned __int16 shaderRegisterEnd)

	: InternalClass()
{
	this->InternalClass.RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	this->InternalClass.NumDescriptors     = (shaderRegisterEnd - shaderRegisterStart + 1);
	this->InternalClass.BaseShaderRegister = shaderRegisterStart;
	this->InternalClass.RegisterSpace      = 0;
	this->InternalClass.Flags              = D3D12_DESCRIPTOR_RANGE_FLAG_NONE;
}

template<>
Uniquis::DirectX12::DescriptorRange<Uniquis::DirectX12::DescriptorRangeType::ConstantBuffers>::DescriptorRange(const unsigned __int16 shaderRegisterStart, const unsigned __int16 shaderRegisterEnd)

	: InternalClass()
{
	this->InternalClass.RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	this->InternalClass.NumDescriptors     = (shaderRegisterEnd - shaderRegisterStart + 1);
	this->InternalClass.BaseShaderRegister = shaderRegisterStart;
	this->InternalClass.RegisterSpace      = 0;
	this->InternalClass.Flags              = D3D12_DESCRIPTOR_RANGE_FLAG_NONE;
}

template<>
Uniquis::DirectX12::DescriptorRange<Uniquis::DirectX12::DescriptorRangeType::Samplers>::DescriptorRange(const unsigned __int16 shaderRegisterStart, const unsigned __int16 shaderRegisterEnd)

	: InternalClass()
{
	this->InternalClass.RangeType          = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
	this->InternalClass.NumDescriptors     = (shaderRegisterEnd - shaderRegisterStart + 1);
	this->InternalClass.BaseShaderRegister = shaderRegisterStart;
	this->InternalClass.RegisterSpace      = 0;
	this->InternalClass.Flags              = D3D12_DESCRIPTOR_RANGE_FLAG_NONE;
}

template<Uniquis::DirectX12::DescriptorRangeType Type>
Uniquis::DirectX12::DescriptorRange<Type>::~DescriptorRange()
{

}

template<Uniquis::DirectX12::DescriptorRangeType Type>
const D3D12_DESCRIPTOR_RANGE1 Uniquis::DirectX12::DescriptorRange<Type>::operator*() const
{
	return this->InternalClass;
}

template class Uniquis::DirectX12::DescriptorRange<Uniquis::DirectX12::DescriptorRangeType::ShaderResources>;
template class Uniquis::DirectX12::DescriptorRange<Uniquis::DirectX12::DescriptorRangeType::UnorderedAccesses>;
template class Uniquis::DirectX12::DescriptorRange<Uniquis::DirectX12::DescriptorRangeType::ConstantBuffers>;
template class Uniquis::DirectX12::DescriptorRange<Uniquis::DirectX12::DescriptorRangeType::Samplers>;
