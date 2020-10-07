#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\CommandList.h"

Uniquis::DirectX12::CommandList::CommandList(const PipelineState<PipelineStateType::Rasterisation>& pPipelineState, const CommandAllocator& pCommandAllocator, const Device& pDevice)
{
	if (FAILED(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, *(pCommandAllocator), *(pPipelineState), IID_PPV_ARGS(&(this->pCommandList)))))
	{
		OutputDebugString(L"[ERROR] !!!!!!!! \n");
	}
}

Uniquis::DirectX12::CommandList::~CommandList()
{
	this->pCommandList->Release();
}

void Uniquis::DirectX12::CommandList::close()
{
	if (FAILED(this->pCommandList->Close()))
	{
		OutputDebugString(L"[ERROR] Failed to close the CommandList \n");
	}
}

void Uniquis::DirectX12::CommandList::reset(const CommandAllocator& commandAllocator, const PipelineState<PipelineStateType::Rasterisation>& pipelineState)
{
	HRESULT hResult;

	hResult = this->pCommandList->Reset(*(commandAllocator), *(pipelineState));

	if (FAILED(hResult))
	{
		OutputDebugString(L"[ERROR] Failed to Reset CommandList");

		_com_error ComError(hResult);
		
		LPCTSTR ComErrorMessage = ComError.ErrorMessage();

		OutputDebugString(std::wstring(L"HRESULT: ").append(ComErrorMessage).append(L"\n").c_str());
	}
}

template<Uniquis::DirectX12::ResourceType Type>
void Uniquis::DirectX12::CommandList::transitionResource(      Uniquis::DirectX12::Resource<Type>& pResource, 
													const Uniquis::DirectX12::ResourceStates& pResourceState) const
{
	pResource.Barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	pResource.Barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	pResource.Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	pResource.Barrier.Transition.StateAfter  = D3D12_RESOURCE_STATES(pResourceState);

	this->pCommandList->ResourceBarrier(1, &(pResource.Barrier));

	pResource.Barrier.Transition.StateBefore = D3D12_RESOURCE_STATES(pResourceState);
}

ID3D12GraphicsCommandList5* Uniquis::DirectX12::CommandList::operator*()  const noexcept
{
	return this->pCommandList;
}

ID3D12GraphicsCommandList5* Uniquis::DirectX12::CommandList::operator->()  const noexcept
{
	return this->pCommandList;
}

template void Uniquis::DirectX12::CommandList::transitionResource(Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Buffer>&    resource, const Uniquis::DirectX12::ResourceStates& resourceState) const;
template void Uniquis::DirectX12::CommandList::transitionResource(Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Texture1D>& resource, const Uniquis::DirectX12::ResourceStates& resourceState) const;
template void Uniquis::DirectX12::CommandList::transitionResource(Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Texture2D>& resource, const Uniquis::DirectX12::ResourceStates& resourceState) const;
template void Uniquis::DirectX12::CommandList::transitionResource(Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Texture3D>& resource, const Uniquis::DirectX12::ResourceStates& resourceState) const;

