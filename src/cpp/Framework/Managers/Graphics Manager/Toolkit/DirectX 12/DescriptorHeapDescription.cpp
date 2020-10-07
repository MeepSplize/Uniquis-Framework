#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\DescriptorHeapDescription.h"

Uniquis::DirectX12::DescriptorHeapDescription::DescriptorHeapDescription(const unsigned __int16 count, const DescriptorHeapFlags& flags)

	: InternalDescription()
{
	this->InternalDescription.NumDescriptors = count;
	this->InternalDescription.Flags          = D3D12_DESCRIPTOR_HEAP_FLAGS(flags);
	this->InternalDescription.NodeMask       = 0;
}

Uniquis::DirectX12::DescriptorHeapDescription::~DescriptorHeapDescription()
{

}

D3D12_DESCRIPTOR_HEAP_DESC& Uniquis::DirectX12::DescriptorHeapDescription::operator*() noexcept
{
	return this->InternalDescription;
}