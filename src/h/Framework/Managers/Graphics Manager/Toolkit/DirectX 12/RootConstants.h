#pragma once

namespace Uniquis::DirectX12
{
	class RootConstants
	{
	private:

		D3D12_ROOT_CONSTANTS InternalClass;

	public:

		RootConstants(const unsigned __int16 shaderRegister, const unsigned __int16 count);

		~RootConstants();

	public:

		void operator=(const RootConstants&) = delete;

		const D3D12_ROOT_CONSTANTS& operator*() const;
	};
}