#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\CommandQueueDesc.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\CommandQueue.h"

Uniquis::DirectX12::CommandQueue::CommandQueue(const Device& pDevice, const CommandQueueFlags& pFlags)
{
	if (FAILED(pDevice->CreateCommandQueue(&(*(CommandQueueDesc(pFlags))), IID_PPV_ARGS(&(this->pCommandQueue)))))
	{
		OutputDebugString(L"[ERROR] CommandQueue Creation Failed! \n");
	}
}

Uniquis::DirectX12::CommandQueue::~CommandQueue()
{
	this->pCommandQueue->Release();
}

void Uniquis::DirectX12::CommandQueue::executeCommandList(CommandList& commandList)
{
	ID3D12CommandList* ppCommandLists[] = { *(commandList) };

	this->pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

void Uniquis::DirectX12::CommandQueue::signal(Fence& pFence)
{
	if (FAILED(this->pCommandQueue->Signal(*(pFence), ++(pFence))))
	{
		OutputDebugString(L"[ERROR] Signalling Fence in Command Queue Failed! \n");
	}
}

ID3D12CommandQueue* Uniquis::DirectX12::CommandQueue::operator*() const noexcept
{
	return this->pCommandQueue;
}

ID3D12CommandQueue* Uniquis::DirectX12::CommandQueue::operator->() const noexcept
{
	return this->pCommandQueue;
}