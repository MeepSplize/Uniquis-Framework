#pragma once

#include "Flags.h"

namespace Uniquis::DirectX12
{
	class DescriptorHeapDescription
	{
	public:

		D3D12_DESCRIPTOR_HEAP_DESC InternalDescription;

	public:

		DescriptorHeapDescription(const unsigned __int16 count, const DescriptorHeapFlags& flags);

		~DescriptorHeapDescription();

	public:

		D3D12_DESCRIPTOR_HEAP_DESC& operator*() noexcept;
	};
}