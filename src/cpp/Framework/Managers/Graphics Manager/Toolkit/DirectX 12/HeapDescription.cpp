#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\HeapDescription.h"

template<Uniquis::DirectX12::HeapType Type>
Uniquis::DirectX12::HeapDescription<Type>::HeapDescription(const unsigned __int64 alignment, const unsigned __int64 byteSize, const HeapFlags& flags)

	: InternalDescription()
{
	this->InternalDescription.SizeInBytes                     = byteSize;
	this->InternalDescription.Properties.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	this->InternalDescription.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	this->InternalDescription.Properties.CreationNodeMask     = 0;
	this->InternalDescription.Properties.VisibleNodeMask      = 0;
	this->InternalDescription.Alignment                       = alignment;
	this->InternalDescription.Flags                           = D3D12_HEAP_FLAGS(flags);
}

template<Uniquis::DirectX12::HeapType Type>
Uniquis::DirectX12::HeapDescription<Type>::HeapDescription(const unsigned __int8 cInputDescriptions, const InternalResourceDescription* pInternalResourceDescriptions, const HeapFlags& flags, const Device& pDevice)

	: InternalDescription()
{
	ResourceAllocationInformation AllocationInformation;
	
	AllocationInformation = pDevice->GetResourceAllocationInfo(0, cInputDescriptions, pInternalResourceDescriptions);

	this->InternalDescription.SizeInBytes                     = AllocationInformation.SizeInBytes;
	this->InternalDescription.Properties.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	this->InternalDescription.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	this->InternalDescription.Properties.CreationNodeMask     = 0;
	this->InternalDescription.Properties.VisibleNodeMask      = 0;
	this->InternalDescription.Alignment                       = AllocationInformation.Alignment;
	this->InternalDescription.Flags                           = D3D12_HEAP_FLAGS(flags);
}

template<Uniquis::DirectX12::HeapType Type>
Uniquis::DirectX12::HeapDescription<Type>::~HeapDescription()
{

}

template<Uniquis::DirectX12::HeapType Type>
const InternalHeapDescription* Uniquis::DirectX12::HeapDescription<Type>::operator*() const noexcept
{
	return &(this->InternalDescription);
}

template class Uniquis::DirectX12::HeapDescription<Uniquis::DirectX12::HeapType::Default>;
template class Uniquis::DirectX12::HeapDescription<Uniquis::DirectX12::HeapType::Upload>;
