#pragma once

#include <WRL.h>

#include "Flags.h"

#include "Device.h"

namespace Uniquis::DirectX12
{
	class CommandAllocator
	{
	private:

		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> pCommandAllocator;

	public:

		CommandAllocator(const Device& device, const CommandAllocatorFlags& flags);

	public:

		~CommandAllocator();

	public:

		void reset();

	public:

		ID3D12CommandAllocator* operator*()  const noexcept;
		ID3D12CommandAllocator* operator->() const noexcept;
	};
}