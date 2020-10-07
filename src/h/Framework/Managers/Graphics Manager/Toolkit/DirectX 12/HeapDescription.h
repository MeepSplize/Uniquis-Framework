#pragma once

#include "Flags.h"
#include "Types.h"

#include "Device.h"

namespace Uniquis::DirectX12
{
	template<HeapType Type>
	class HeapDescription
	{
	public:

		InternalHeapDescription InternalDescription;

	public:

		HeapDescription(const unsigned __int64 alignment, const unsigned __int64 byteSize, const HeapFlags& flags);

		HeapDescription(const unsigned __int8 cInputDescriptions, const InternalResourceDescription* pInternalResourceDescriptions, const HeapFlags& flags, const Device& pDevice);

	public:

		~HeapDescription();

		const InternalHeapDescription* operator*() const noexcept;
	};
}