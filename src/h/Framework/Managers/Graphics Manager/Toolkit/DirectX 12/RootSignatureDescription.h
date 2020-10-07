#pragma once

#include "RootParameter.h"
#include "StaticSampler.h"
#include "RootDescriptorTable.h"
#include "RootConstants.h"

namespace Uniquis::DirectX12
{
	class RootSignatureDescription
	{
	public:

		D3D12_VERSIONED_ROOT_SIGNATURE_DESC InternalDescription;

	public:

		std::vector<RootParameter> vRootParameters;
		std::vector<StaticSampler> vStaticSamplers;

	public:

		RootSignatureDescription() = delete;

		RootSignatureDescription(const std::vector<RootParameter> vRootParameters,
								 const std::vector<StaticSampler> vStaticSamplers);

		~RootSignatureDescription();

	public:

		void operator=(const RootSignatureDescription&) = delete;

		const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& operator*() const;
	};
}