#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\CommandQueueDesc.h"

Uniquis::DirectX12::CommandQueueDesc::CommandQueueDesc(const CommandQueueFlags& flags)
{
	if (flags == CommandQueueFlags::NONE)
	{
		this->CommandQueueDescStruct.Type     = D3D12_COMMAND_LIST_TYPE_DIRECT;
		this->CommandQueueDescStruct.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		this->CommandQueueDescStruct.Flags    = D3D12_COMMAND_QUEUE_FLAG_NONE;
		this->CommandQueueDescStruct.NodeMask = 0;
	}
}

Uniquis::DirectX12::CommandQueueDesc::~CommandQueueDesc()
{

}

D3D12_COMMAND_QUEUE_DESC Uniquis::DirectX12::CommandQueueDesc::operator*() const {

	return this->CommandQueueDescStruct;
}