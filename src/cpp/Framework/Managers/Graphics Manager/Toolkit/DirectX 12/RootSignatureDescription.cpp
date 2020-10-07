#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\RootSignatureDescription.h"

Uniquis::DirectX12::RootSignatureDescription::RootSignatureDescription(const std::vector<RootParameter> vRootParameters,
															     	   const std::vector<StaticSampler> vStaticSamplers)
	
	: vRootParameters(vRootParameters),
	  vStaticSamplers(vStaticSamplers)
{
	D3D12_ROOT_PARAMETER1* pInternalRootParameters = reinterpret_cast<D3D12_ROOT_PARAMETER1*>(malloc(this->vRootParameters.size() * sizeof(D3D12_ROOT_PARAMETER1)));

	if (pInternalRootParameters == nullptr)
	{
		__debugbreak();
	}

	for (unsigned __int8 i = 0; i < this->vRootParameters.size(); i++)
	{
		pInternalRootParameters[i] = *(this->vRootParameters[i]);
	}

	D3D12_STATIC_SAMPLER_DESC* pInternalStaticSamplerDescriptions = reinterpret_cast<D3D12_STATIC_SAMPLER_DESC*>(malloc(this->vStaticSamplers.size() * sizeof(D3D12_STATIC_SAMPLER_DESC)));

	if (pInternalStaticSamplerDescriptions == nullptr)
	{
		__debugbreak();
	}

	for (unsigned __int8 i = 0; i < this->vStaticSamplers.size(); i++)
	{
		pInternalStaticSamplerDescriptions[i] = *(this->vStaticSamplers[i]);
	}

	D3D12_ROOT_SIGNATURE_DESC1 Description = {};

	Description.NumParameters     = this->vRootParameters.size();
	Description.pParameters       = pInternalRootParameters;
	Description.NumStaticSamplers = this->vStaticSamplers.size();
	Description.pStaticSamplers   = pInternalStaticSamplerDescriptions;
	Description.Flags             = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | 
									D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | 
									D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | 
									D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;

	this->InternalDescription.Version  = D3D_ROOT_SIGNATURE_VERSION_1_0;
	this->InternalDescription.Desc_1_1 = Description;
}

Uniquis::DirectX12::RootSignatureDescription::~RootSignatureDescription()
{

}

const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& Uniquis::DirectX12::RootSignatureDescription::operator*() const
{
	return this->InternalDescription;
}