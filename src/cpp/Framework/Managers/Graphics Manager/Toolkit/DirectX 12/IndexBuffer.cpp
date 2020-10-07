#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\IndexBuffer.h"

Uniquis::DirectX12::IndexBuffer::IndexBuffer(      std::vector<unsigned __int32> vIndices, 
										const CommandList&                  pCommandList, 
										const Device&                       pDevice)

	:   vIndices(vIndices),
	  Descriptor()
{
	/* Variables */

	SubresourceData Data = {};

	/* Descriptions */

	ResourceDescription<ResourceType::Buffer> IndexBufferDescription((this->vIndices.size() * sizeof(unsigned __int32)), 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::COPY_DESTINATION, ResourceCreation::PLACED, ResourceFlags::NONE);

	HeapDescription<HeapType::Default> DefaultHeapDescription(1, *(IndexBufferDescription), HeapFlags::ALLOW_ONLY_BUFFERS, pDevice);

	HeapDescription<HeapType::Upload> UploadHeapDescription(1, *(IndexBufferDescription), HeapFlags::ALLOW_ONLY_BUFFERS, pDevice);
			
	Data.pData      = reinterpret_cast<BYTE*>(this->vIndices.data());
	Data.RowPitch   = (this->vIndices.size() * sizeof(unsigned __int32));
	Data.SlicePitch = (this->vIndices.size() * sizeof(unsigned __int32));

	/* Initialization */

	this->pDefaultHeap = std::make_shared<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);

	this->pUploadHeap = std::make_shared<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

	this->pResource = std::make_unique<Resource<ResourceType::Buffer>>(0, IndexBufferDescription, *(this->pDefaultHeap), pDevice);

	IndexBufferDescription.ResourceState = ResourceStates::GENERIC_READ;

	this->pUpload = std::make_unique<Resource<ResourceType::Buffer>>(0, IndexBufferDescription, *(this->pUploadHeap), pDevice);

	/* Update */

	UpdateSubresources(*(pCommandList), **(this->pResource), **(this->pUpload), 0, 0, 1, &(Data));

	pCommandList.transitionResource(*(this->pResource), ResourceStates::INDEX_BUFFER);

	/* Descriptor */

	this->Descriptor.BufferLocation = (*(this->pResource))->GetGPUVirtualAddress();
	this->Descriptor.SizeInBytes    = (this->vIndices.size() * sizeof(unsigned __int32));
	this->Descriptor.Format         = DXGI_FORMAT_R32_UINT;
}

Uniquis::DirectX12::IndexBuffer::IndexBuffer(const unsigned __int64                                    defaultHeapOffset,
										const unsigned __int64                                    uploadHeapOffset,
										const          std::vector<unsigned __int32>              vIndices,
										const          std::shared_ptr<Heap<HeapType::Default>>& ppDefaultHeap,
										const          std::shared_ptr<Heap<HeapType::Upload>>&  ppUploadHeap,
										const          CommandList&                               pCommandList, 
										const          Device&                                    pDevice)

	:     vIndices(vIndices),
	    Descriptor(),
	  pDefaultHeap(ppDefaultHeap),
	   pUploadHeap(ppUploadHeap)
{
	/* Variables */

	SubresourceData Data = {};

	/* Descriptions */

	ResourceDescription<ResourceType::Buffer> IndexBufferDescription((this->vIndices.size() * sizeof(unsigned __int32)), 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::COPY_DESTINATION, ResourceCreation::PLACED, ResourceFlags::NONE);
			
	Data.pData      = reinterpret_cast<BYTE*>(this->vIndices.data());
	Data.RowPitch   = (this->vIndices.size() * sizeof(unsigned __int32));
	Data.SlicePitch = (this->vIndices.size() * sizeof(unsigned __int32));

	/* Initialization */

	this->pResource = std::make_unique<Resource<ResourceType::Buffer>>(defaultHeapOffset, IndexBufferDescription, *(this->pDefaultHeap), pDevice);

	IndexBufferDescription.ResourceState = ResourceStates::GENERIC_READ;

	this->pUpload = std::make_unique<Resource<ResourceType::Buffer>>(uploadHeapOffset, IndexBufferDescription, *(this->pUploadHeap), pDevice);

	/* Update */

	UpdateSubresources(*(pCommandList), **(this->pResource), **(this->pUpload), 0, 0, 1, &(Data));

	pCommandList.transitionResource(*(this->pResource), ResourceStates::INDEX_BUFFER);

	/* Descriptor */

	this->Descriptor.BufferLocation = (*(this->pResource))->GetGPUVirtualAddress();
	this->Descriptor.SizeInBytes    = (this->vIndices.size() * sizeof(unsigned __int32));
	this->Descriptor.Format         = DXGI_FORMAT_R32_UINT;
}

Uniquis::DirectX12::IndexBuffer::~IndexBuffer()
{

}

void Uniquis::DirectX12::IndexBuffer::update(const CommandList& pCommandList)
{
	BYTE* pVertexDataBegin;
	
	CD3DX12_RANGE ReadRange(0, 0); 
	
	(*(this->pUpload))->Map(0, &(ReadRange), reinterpret_cast<void**>(&(pVertexDataBegin)));
	
	memcpy(pVertexDataBegin, this->vIndices.data(), (this->vIndices.size() * sizeof(unsigned __int32)));
	
	(*(this->pUpload))->Unmap(0, nullptr);
	
	pCommandList.transitionResource(*(this->pResource), ResourceStates::COPY_DESTINATION);
	
	pCommandList->CopyResource(**(this->pResource), **(this->pUpload));
	
	pCommandList.transitionResource(*(this->pResource), ResourceStates::INDEX_BUFFER);
}

ID3D12Resource* Uniquis::DirectX12::IndexBuffer::operator*() const
{
	return (**(this->pResource));
}