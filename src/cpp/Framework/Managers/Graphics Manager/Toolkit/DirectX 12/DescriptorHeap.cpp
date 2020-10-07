#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\DescriptorHeap.h"

template<Uniquis::DirectX12::DescriptorHeapType Type>
Uniquis::DirectX12::DescriptorHeap<Type>::DescriptorHeap(DescriptorHeapDescription& pDescription, const Device& pDevice)
{
	
}

template<>
Uniquis::DirectX12::DescriptorHeap<Uniquis::DirectX12::DescriptorHeapType::CommonDescriptors>::DescriptorHeap(DescriptorHeapDescription& pDescription, const Device& pDevice)

	: CPUHandle(),
	  GPUHandle()
{
	pDescription.InternalDescription.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	if (FAILED(pDevice->CreateDescriptorHeap(&(*(pDescription)), IID_PPV_ARGS(&(this->pDescriptorHeap)))))
	{
		OutputDebugString(L"[ERROR] Descriptor Heap Creation Failed \n");
	}

	this->IncrementSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	this->vPartitionDescriptors.emplace_back(pDescription.InternalDescription.NumDescriptors);
	
	this->CPUHandle = this->pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	this->GPUHandle = this->pDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
}

template<>
Uniquis::DirectX12::DescriptorHeap<Uniquis::DirectX12::DescriptorHeapType::DepthStencilDescriptors>::DescriptorHeap(DescriptorHeapDescription& pDescription, const Device& pDevice)

	: CPUHandle(),
	  GPUHandle()
{
	pDescription.InternalDescription.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

	if (FAILED(pDevice->CreateDescriptorHeap(&(*(pDescription)), IID_PPV_ARGS(&(this->pDescriptorHeap)))))
	{
		OutputDebugString(L"[ERROR] Descriptor Heap Creation Failed \n");
	}

	this->IncrementSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	this->vPartitionDescriptors.emplace_back(pDescription.InternalDescription.NumDescriptors);
		
	this->CPUHandle = this->pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	this->GPUHandle = this->pDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
}

template<>
Uniquis::DirectX12::DescriptorHeap<Uniquis::DirectX12::DescriptorHeapType::RenderTargetDescriptors>::DescriptorHeap(DescriptorHeapDescription& pDescription, const Device& pDevice)

	: CPUHandle(),
	  GPUHandle()
{
	pDescription.InternalDescription.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	if (FAILED(pDevice->CreateDescriptorHeap(&(*(pDescription)), IID_PPV_ARGS(&(this->pDescriptorHeap)))))
	{
		OutputDebugString(L"[ERROR] Descriptor Heap Creation Failed \n");
	}

	this->IncrementSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	this->vPartitionDescriptors.emplace_back(pDescription.InternalDescription.NumDescriptors);

	this->CPUHandle = this->pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	this->GPUHandle = this->pDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
}

template<>
Uniquis::DirectX12::DescriptorHeap<Uniquis::DirectX12::DescriptorHeapType::SamplerDescriptors>::DescriptorHeap(DescriptorHeapDescription& pDescription, const Device& pDevice)

	: CPUHandle(),
	  GPUHandle()
{
	pDescription.InternalDescription.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;

	if (FAILED(pDevice->CreateDescriptorHeap(&(*(pDescription)), IID_PPV_ARGS(&(this->pDescriptorHeap)))))
	{
		OutputDebugString(L"[ERROR] Descriptor Heap Creation Failed \n");
	}

	this->IncrementSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

	this->vPartitionDescriptors.emplace_back(pDescription.InternalDescription.NumDescriptors);

	this->CPUHandle = this->pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	this->GPUHandle = this->pDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
}

template<Uniquis::DirectX12::DescriptorHeapType Type>
D3D12_CPU_DESCRIPTOR_HANDLE Uniquis::DirectX12::DescriptorHeap<Type>::getCPUHandleToDescriptor(const unsigned __int32 index) noexcept
{
	D3D12_CPU_DESCRIPTOR_HANDLE Handle = this->CPUHandle;

	Handle.ptr += (index * this->IncrementSize);

	return (std::move(Handle));
}

template<Uniquis::DirectX12::DescriptorHeapType Type>
D3D12_GPU_DESCRIPTOR_HANDLE Uniquis::DirectX12::DescriptorHeap<Type>::getGPUHandleToDescriptor(const unsigned __int32 index) noexcept
{
	D3D12_GPU_DESCRIPTOR_HANDLE Handle = this->GPUHandle;

	Handle.ptr += (index * this->IncrementSize);

	return (std::move(Handle));
}

template<Uniquis::DirectX12::DescriptorHeapType Type>
unsigned __int32 Uniquis::DirectX12::DescriptorHeap<Type>::addDescriptor(unsigned __int16 iPartition, ConstantBufferDescriptorDescription& description, const Device& pDevice)
{
	if ((this->vPartitionDescriptors[iPartition].End - this->vPartitionDescriptors[iPartition].Begin) == this->vPartitionDescriptors[iPartition].Occupied)
	{
		OutputDebugString(L"[WARNING] Tried creating a Descriptor in a full Descriptor Heap! \n");

		return 0;
	}
	else
	{
		D3D12_CPU_DESCRIPTOR_HANDLE Handle = this->CPUHandle;

		Handle.ptr += (this->IncrementSize * (this->vPartitionDescriptors[iPartition].Begin + this->vPartitionDescriptors[iPartition].Occupied));

		pDevice->CreateConstantBufferView(&(description), Handle);
		
		this->vPartitionDescriptors[iPartition]++;

		return this->vPartitionDescriptors[iPartition].Occupied;
	}
}

template<Uniquis::DirectX12::DescriptorHeapType Type>
Uniquis::DirectX12::DescriptorHeap<Type>::~DescriptorHeap()
{
	this->pDescriptorHeap->Release();
}

template<Uniquis::DirectX12::DescriptorHeapType Type>
ID3D12DescriptorHeap* Uniquis::DirectX12::DescriptorHeap<Type>::operator*() const noexcept
{
	return this->pDescriptorHeap;
}

template<Uniquis::DirectX12::DescriptorHeapType Type>
ID3D12DescriptorHeap* Uniquis::DirectX12::DescriptorHeap<Type>::operator->() const noexcept
{
	return this->pDescriptorHeap;
}

template class Uniquis::DirectX12::DescriptorHeap<Uniquis::DirectX12::DescriptorHeapType::CommonDescriptors>;
template class Uniquis::DirectX12::DescriptorHeap<Uniquis::DirectX12::DescriptorHeapType::DepthStencilDescriptors>;
template class Uniquis::DirectX12::DescriptorHeap<Uniquis::DirectX12::DescriptorHeapType::RenderTargetDescriptors>;
template class Uniquis::DirectX12::DescriptorHeap<Uniquis::DirectX12::DescriptorHeapType::SamplerDescriptors>;
