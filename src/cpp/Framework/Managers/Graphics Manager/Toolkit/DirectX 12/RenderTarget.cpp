#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\RenderTarget.h"

Uniquis::DirectX12::RenderTarget::RenderTarget(const unsigned __int32                                                      width,
					                      const unsigned __int32                                                      height,
	                                                     DescriptorHeap<DescriptorHeapType::RenderTargetDescriptors>& pDescriptorHeap,
					                      const          Device&                                                      pDevice)

	:     pHeap(),
	  pResource()
{
	/* Descriptions */

	ResourceDescription<ResourceType::Texture2D> ResourceDescription(width, height, 1, 0, DXGI_FORMAT_R8G8B8A8_UNORM, SampleDescription(1, 0), &(ClearValue(1.0f, 0)), ResourceStates::DEPTH_WRITE, ResourceCreation::PLACED, ResourceFlags::ALLOW_DEPTH_STENCIL);

	HeapDescription<HeapType::Default> HeapDescription(1, *(ResourceDescription), HeapFlags::ALLOW_ONLY_RT_DS_TEXTURES, pDevice);

	D3D12_TEX2D_RTV RenderTargetResourceDescription = {};

	RenderTargetResourceDescription.MipSlice   = 0;
	RenderTargetResourceDescription.PlaneSlice = 0;

	D3D12_RENDER_TARGET_VIEW_DESC DescriptorDescription = {};

	DescriptorDescription.Format        = DXGI_FORMAT_R8G8B8A8_UNORM;
	DescriptorDescription.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	DescriptorDescription.Texture2D     = RenderTargetResourceDescription;

	/* Initialization */

	this->pHeap = std::make_unique<Heap<HeapType::Default>>(HeapDescription, pDevice);

	this->pResource = std::make_unique<Resource<ResourceType::Texture2D>>(0, ResourceDescription, *(this->pHeap), pDevice);

	/* Descriptor */

	D3D12_CPU_DESCRIPTOR_HANDLE Handle = pDescriptorHeap.getCPUHandleToDescriptor(pDescriptorHeap.vPartitionDescriptors[0].Occupied);

	pDevice->CreateRenderTargetView(**(this->pResource), &(DescriptorDescription), Handle);
}