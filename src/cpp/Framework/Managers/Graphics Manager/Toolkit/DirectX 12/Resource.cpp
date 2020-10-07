#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Resource.h"

template<Uniquis::DirectX12::ResourceType Type>
Uniquis::DirectX12::Resource<Type>::Resource(const unsigned __int64                                   heapOffset,
										               Uniquis::DirectX12::ResourceDescription<Type>& description,
										const          Uniquis::DirectX12::Heap<HeapType::Default>&  heap,
										const          Uniquis::DirectX12::Device&                    device)

	: pResource(),
	  Barrier()
{
	HRESULT hResult;

	switch (description.ResourceCreation)
	{
		case ResourceCreation::PLACED:
		{
			hResult = device->CreatePlacedResource(*(heap), heapOffset, *(description), D3D12_RESOURCE_STATES(description.ResourceState), **(description.pClearValue), IID_PPV_ARGS(&(this->pResource)));
			
			if (FAILED(hResult))
			{
				std::string Error = std::system_category().message(hResult);

				OutputDebugString(L"[ERROR] Creation of Placed Resource Failed! \n");
				OutputDebugStringA(Error.append("\n").c_str());
			}

			break;
		}

		case ResourceCreation::RESERVED:
		{
			if (FAILED(device->CreateReservedResource(*(description), D3D12_RESOURCE_STATES(description.ResourceState), **(description.pClearValue), IID_PPV_ARGS(&(this->pResource)))))
			{
				OutputDebugString(L"[ERROR] Creation of Reserved Resource Failed!");
			}

			break;
		}
	}

	this->Barrier.Transition.pResource   = this->pResource;
	this->Barrier.Transition.StateBefore = D3D12_RESOURCE_STATES(description.ResourceState);
}

template<>
Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Buffer>::Resource(const unsigned __int64                                                   heapOffset,
																	                  Uniquis::DirectX12::ResourceDescription<ResourceType::Buffer>& description,
																	   const          Uniquis::DirectX12::Heap<HeapType::Default>&                   heap,
																	   const          Uniquis::DirectX12::Device&                                     device)

	: pResource(),
	  Barrier()
{
	switch (description.ResourceCreation)
	{
		case ResourceCreation::PLACED:
		{
			if (FAILED(device->CreatePlacedResource(*(heap), heapOffset, *(description), D3D12_RESOURCE_STATES(description.ResourceState), nullptr, IID_PPV_ARGS(&(this->pResource)))))
			{
				OutputDebugString(L"[ERROR] Creation of Placed Resource Failed!");
			}

			break;
		}

		case ResourceCreation::RESERVED:
		{
			if (FAILED(device->CreateReservedResource(*(description), D3D12_RESOURCE_STATES(description.ResourceState), nullptr, IID_PPV_ARGS(&(this->pResource)))))
			{
				OutputDebugString(L"[ERROR] Creation of Reserved Resource Failed!");
			}

			break;
		}
	}

	this->Barrier.Transition.pResource   = this->pResource;
	this->Barrier.Transition.StateBefore = D3D12_RESOURCE_STATES(description.ResourceState);
}

template<Uniquis::DirectX12::ResourceType Type>
Uniquis::DirectX12::Resource<Type>::Resource(const unsigned __int64                                   heapOffset,
										               Uniquis::DirectX12::ResourceDescription<Type>& description,
										const          Uniquis::DirectX12::Heap<HeapType::Upload>&   heap,
										const          Uniquis::DirectX12::Device&                    device)

	: pResource(),
	  Barrier()
{
	switch (description.ResourceCreation)
	{
		case ResourceCreation::PLACED:
		{
			if (FAILED(device->CreatePlacedResource(*(heap), heapOffset, *(description), D3D12_RESOURCE_STATES(description.ResourceState), **(description.pClearValue), IID_PPV_ARGS(&(this->pResource)))))
			{
				OutputDebugString(L"[ERROR] Creation of Placed Resource Failed!");
			}

			break;
		}

		case ResourceCreation::RESERVED:
		{
			if (FAILED(device->CreateReservedResource(*(description), D3D12_RESOURCE_STATES(description.ResourceState), **(description.pClearValue), IID_PPV_ARGS(&(this->pResource)))))
			{
				OutputDebugString(L"[ERROR] Creation of Reserved Resource Failed!");
			}

			break;
		}
	}

	this->Barrier.Transition.pResource   = this->pResource;
	this->Barrier.Transition.StateBefore = D3D12_RESOURCE_STATES(description.ResourceState);
}

template<>
Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Buffer>::Resource(const unsigned __int64                                                   heapOffset,
																	                  Uniquis::DirectX12::ResourceDescription<ResourceType::Buffer>& description,
																	   const          Uniquis::DirectX12::Heap<HeapType::Upload>&                    heap,
																	   const          Uniquis::DirectX12::Device&                                     device)

	: pResource(),
	  Barrier()
{
	HRESULT hResult;

	switch (description.ResourceCreation)
	{
		case ResourceCreation::PLACED:
		{
			hResult = device->CreatePlacedResource(*(heap), heapOffset, *(description), D3D12_RESOURCE_STATES(description.ResourceState), nullptr, IID_PPV_ARGS(&(this->pResource)));
			
			if (FAILED(hResult))
			{
				std::string Error = std::system_category().message(hResult);

				OutputDebugString(L"[ERROR] Creation of Placed Resource Failed! \n");
				OutputDebugStringA(Error.append("\n").c_str());
			}

			break;
		}

		case ResourceCreation::RESERVED:
		{
			if (FAILED(device->CreateReservedResource(*(description), D3D12_RESOURCE_STATES(description.ResourceState), nullptr, IID_PPV_ARGS(&(this->pResource)))))
			{
				OutputDebugString(L"[ERROR] Creation of Reserved Resource Failed!");
			}

			break;
		}
	}

	this->Barrier.Transition.pResource   = this->pResource;
	this->Barrier.Transition.StateBefore = D3D12_RESOURCE_STATES(description.ResourceState);
}

template<Uniquis::DirectX12::ResourceType Type>
Uniquis::DirectX12::Resource<Type>::~Resource()
{
	this->pResource->Release();
}

template<Uniquis::DirectX12::ResourceType Type>
ID3D12Resource* Uniquis::DirectX12::Resource<Type>::operator*() const noexcept
{
	return this->pResource;
}

template<Uniquis::DirectX12::ResourceType Type>
ID3D12Resource* Uniquis::DirectX12::Resource<Type>::operator->() const noexcept
{
	return this->pResource;
}

template class Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Buffer>;
template class Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Texture1D>;
template class Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Texture2D>;
template class Uniquis::DirectX12::Resource<Uniquis::DirectX12::ResourceType::Texture3D>;

