#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\StaticSampler.h"

Uniquis::DirectX12::StaticSampler::StaticSampler()

	: InternalDescription()
{
	this->InternalDescription.Filter           = D3D12_FILTER_MIN_MAG_MIP_POINT;
	this->InternalDescription.AddressU         = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	this->InternalDescription.AddressV         = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	this->InternalDescription.AddressW         = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	this->InternalDescription.MipLODBias       = 0;
	this->InternalDescription.MaxAnisotropy    = 0;
	this->InternalDescription.ComparisonFunc   = D3D12_COMPARISON_FUNC_NEVER;
	this->InternalDescription.BorderColor      = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	this->InternalDescription.MinLOD           = 0.0f;
	this->InternalDescription.MaxLOD           = D3D12_FLOAT32_MAX;
	this->InternalDescription.ShaderRegister   = 0;
	this->InternalDescription.RegisterSpace    = 0;
	this->InternalDescription.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
}

Uniquis::DirectX12::StaticSampler::~StaticSampler()
{

}

D3D12_STATIC_SAMPLER_DESC& Uniquis::DirectX12::StaticSampler::operator*() noexcept
{
	return this->InternalDescription;
}