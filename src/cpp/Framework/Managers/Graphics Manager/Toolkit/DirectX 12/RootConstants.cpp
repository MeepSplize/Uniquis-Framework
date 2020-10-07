#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\RootConstants.h"

Uniquis::DirectX12::RootConstants::RootConstants(const unsigned __int16 shaderRegister, const unsigned __int16 count)

	: InternalClass()
{
	InternalClass.ShaderRegister = shaderRegister;
	InternalClass.RegisterSpace  = 0;
	InternalClass.Num32BitValues = count;
}

Uniquis::DirectX12::RootConstants::~RootConstants()
{

}

const D3D12_ROOT_CONSTANTS& Uniquis::DirectX12::RootConstants::operator*() const
{
	return this->InternalClass;
}