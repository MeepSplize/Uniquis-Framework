#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\HeapDescription.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\DepthBuffer.h"

Uniquis::DirectX12::DepthBuffer::DepthBuffer(const unsigned __int32                                                      width,
										const unsigned __int32                                                      height,
										               DescriptorHeap<DescriptorHeapType::DepthStencilDescriptors>& pDescriptorHeap,
										const          Device&                                                      pDevice)
{
	/* Descriptions */

	ResourceDescription<ResourceType::Texture2D> ResourceDescription(width, height, 1, 0, DXGI_FORMAT_D32_FLOAT, SampleDescription(1, 0), &(ClearValue(1.0f, 0)), ResourceStates::DEPTH_WRITE, ResourceCreation::PLACED, ResourceFlags::ALLOW_DEPTH_STENCIL);

	HeapDescription<HeapType::Default> HeapDescription(1, *(ResourceDescription), HeapFlags::ALLOW_ONLY_RT_DS_TEXTURES, pDevice);

	DepthStencilViewDescription DescriptorDescription = {};
	
	DescriptorDescription.Format             = DXGI_FORMAT_D32_FLOAT;
	DescriptorDescription.ViewDimension      = D3D12_DSV_DIMENSION_TEXTURE2D;
	DescriptorDescription.Texture2D.MipSlice = 0;
	DescriptorDescription.Flags              = D3D12_DSV_FLAG_NONE;

	/* Initialization */

	this->pHeap = std::make_unique<Heap<HeapType::Default>>(HeapDescription, pDevice);

	this->pResource = std::make_unique<Resource<ResourceType::Texture2D>>(0, ResourceDescription, *(this->pHeap), pDevice);

	/* Descriptor */

	this->Handle = pDescriptorHeap.getCPUHandleToDescriptor(pDescriptorHeap.vPartitionDescriptors[0].Occupied);

	pDevice->CreateDepthStencilView(**(this->pResource), &(DescriptorDescription), this->Handle);
}

Uniquis::DirectX12::DepthBuffer::~DepthBuffer()
{

}

void Uniquis::DirectX12::DepthBuffer::clear(const CommandList& pCommandList)
{
	pCommandList->ClearDepthStencilView(this->Handle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

D3D12_CPU_DESCRIPTOR_HANDLE* Uniquis::DirectX12::DepthBuffer::operator*() noexcept
{
	return &(this->Handle);
}