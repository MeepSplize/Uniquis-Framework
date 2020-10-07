#pragma once

#include "Device.h"
#include "RootSignatureDescription.h"

namespace Uniquis::DirectX12
{
	class RootSignature
	{
	private:

		ID3D12RootSignature* pRootSignature;

		ID3DBlob* pRootSignatureBlob;
		ID3DBlob* pError;

	public:

		RootSignature(const RootSignatureDescription& pDescription,
					  const Device&                   pDevice);

		~RootSignature();

	public:

		void operator=(const RootSignature&) = delete;

		ID3D12RootSignature* operator*()  const;
		ID3D12RootSignature* operator->() const;
	};
}