#pragma once

namespace Uniquis::DirectX12
{
	class StaticSampler
	{
	public:

		D3D12_STATIC_SAMPLER_DESC InternalDescription;

	public:

		StaticSampler();

		~StaticSampler();

	public:

		void operator=(const StaticSampler&) = delete;

		D3D12_STATIC_SAMPLER_DESC& operator*() noexcept;
	};
}