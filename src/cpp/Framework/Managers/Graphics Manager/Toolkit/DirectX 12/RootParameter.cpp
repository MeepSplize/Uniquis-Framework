#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\RootParameter.h"

Uniquis::DirectX12::RootParameter::RootParameter(const RootConstants&    pRootConstants, 
											const ShaderVisibility& shaderVisibility)

	: Description()
{
	std::underlying_type<ShaderVisibility>::type UNDERLYING_TYPE = std::underlying_type<ShaderVisibility>::type(shaderVisibility);

	D3D12_SHADER_VISIBILITY VISIBILITY = D3D12_SHADER_VISIBILITY(static_cast<__int32>(UNDERLYING_TYPE));

	this->Description.ParameterType    = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	this->Description.Constants        = *(pRootConstants);
	this->Description.ShaderVisibility = D3D12_SHADER_VISIBILITY(static_cast<__int32>(std::underlying_type<ShaderVisibility>::type(shaderVisibility)));
}

Uniquis::DirectX12::RootParameter::RootParameter(const RootDescriptorTable& pRootDescriptorTable, 
											const ShaderVisibility&    shaderVisibility)

	: Description()
{
	this->Description.ParameterType   = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	this->Description.DescriptorTable = *(pRootDescriptorTable);
	this->Description.ShaderVisibility = D3D12_SHADER_VISIBILITY(std::underlying_type<ShaderVisibility>::type(shaderVisibility));
}

Uniquis::DirectX12::RootParameter::~RootParameter()
{

}

const D3D12_ROOT_PARAMETER1& Uniquis::DirectX12::RootParameter::operator*() const
{
	return this->Description;
}