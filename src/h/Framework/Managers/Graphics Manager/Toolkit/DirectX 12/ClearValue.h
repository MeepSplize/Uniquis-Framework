#pragma once

namespace Uniquis::DirectX12
{
	class ClearValue
	{
	public:

		D3D12_CLEAR_VALUE InternalValue;

	public:

		ClearValue(const std::initializer_list<float> colorValues);
		ClearValue(float color[4]);
		ClearValue(float depthValue, unsigned __int8 stencilValue);

	public:

		~ClearValue();

	public:

		D3D12_CLEAR_VALUE* operator*() noexcept;
	};
}