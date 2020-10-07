#pragma once

namespace Uniquis::DirectX12
{
	enum class DescriptorRangeType : unsigned __int8
	{
		ShaderResources,
		UnorderedAccesses,
		ConstantBuffers,
		Samplers
	};

	template<DescriptorRangeType>
	class DescriptorRange
	{
	private:

		D3D12_DESCRIPTOR_RANGE1 InternalClass;

	public:

		DescriptorRange(const unsigned __int16 shaderRegisterStart, const unsigned __int16 shaderRegisterEnd);

		DescriptorRange(const DescriptorRange&) = delete;

		DescriptorRange(const DescriptorRange&&) = delete;

		~DescriptorRange();

	public:

		void operator=(const DescriptorRange&) = delete;

		const D3D12_DESCRIPTOR_RANGE1 operator*() const;
	};
}