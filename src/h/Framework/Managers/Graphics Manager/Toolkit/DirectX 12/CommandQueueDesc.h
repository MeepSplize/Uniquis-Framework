#pragma once

#include "Flags.h"

namespace Uniquis::DirectX12
{
	struct CommandQueueDesc
	{
	private:

		D3D12_COMMAND_QUEUE_DESC CommandQueueDescStruct;

	public:

		CommandQueueDesc(const CommandQueueFlags& flags);

		~CommandQueueDesc();

	public:

		D3D12_COMMAND_QUEUE_DESC operator*() const;
	};
}