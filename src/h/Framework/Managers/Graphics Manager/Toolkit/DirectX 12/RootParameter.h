#pragma once

#include "RootDescriptorTable.h"
#include "RootConstants.h"
#include "Types.h"

namespace Uniquis::DirectX12
{
	class RootParameter
	{
	private:

		D3D12_ROOT_PARAMETER1 Description;

	public:

		RootParameter() = delete;

		RootParameter(const RootConstants&    pRootConstants, 
					  const ShaderVisibility& shaderVisibility);

		RootParameter(const RootDescriptorTable& pRootDescriptorTable, 
					  const ShaderVisibility&    shaderVisibility);

		~RootParameter();

	public:

		void operator=(const RootParameter&) = delete;

		const D3D12_ROOT_PARAMETER1& operator*() const;
	};
}