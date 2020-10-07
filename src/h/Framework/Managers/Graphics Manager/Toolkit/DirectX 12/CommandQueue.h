#pragma once

#include <WRL.h>

#include "Flags.h"

#include "Device.h"
#include "CommandList.h"
#include "Fence.h"

namespace Uniquis::DirectX12 
{
	class CommandQueue
	{
	private:

		ID3D12CommandQueue* pCommandQueue;

	public:

		CommandQueue(const Device& pDevice, const CommandQueueFlags& pFlags);

		~CommandQueue();

	public:

		void executeCommandList(CommandList& commandList);
		void signal(Fence& fence);

	public:

		ID3D12CommandQueue* operator*()  const noexcept;
		ID3D12CommandQueue* operator->() const noexcept;
	};
}