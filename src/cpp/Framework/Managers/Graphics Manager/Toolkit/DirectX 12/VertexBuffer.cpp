#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\VertexBuffer.h"

Uniquis::DirectX12::VertexBuffer::VertexBuffer(const std::vector<Vertex> vVertices, 
										       const CommandList&        pCommandList, 
										       const Device&             pDevice)

	:  vVertices(vVertices),
	  Descriptor()
{
	/* Variables */

	SubresourceData Data = {};

	/* Descriptions */

	ResourceDescription<ResourceType::Buffer> VertexBufferDescription((this->vVertices.size() * sizeof(Vertex)), 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::COPY_DESTINATION, ResourceCreation::PLACED, ResourceFlags::NONE);

	HeapDescription<HeapType::Default> DefaultHeapDescription(1, *(VertexBufferDescription), HeapFlags::ALLOW_ONLY_BUFFERS, pDevice);

	HeapDescription<HeapType::Upload> UploadHeapDescription(1, *(VertexBufferDescription), HeapFlags::ALLOW_ONLY_BUFFERS, pDevice);

	Data.pData      = reinterpret_cast<BYTE*>(this->vVertices.data());
	Data.RowPitch   = (this->vVertices.size() * sizeof(Vertex));
	Data.SlicePitch = (this->vVertices.size() * sizeof(Vertex));

	/* Initialization */

	this->pDefaultHeap = std::make_shared<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);

	this->pUploadHeap = std::make_shared<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

	this->pResource = std::make_unique<Resource<ResourceType::Buffer>>(0, VertexBufferDescription, *(this->pDefaultHeap), pDevice);

	VertexBufferDescription.ResourceState = ResourceStates::GENERIC_READ;

	this->pUpload = std::make_unique<Resource<ResourceType::Buffer>>(0, VertexBufferDescription, *(this->pUploadHeap), pDevice);

	/* Update */

	UpdateSubresources(*(pCommandList), **(this->pResource), **(this->pUpload), 0, 0, 1, &(Data));

	pCommandList->ResourceBarrier(1, &(CD3DX12_RESOURCE_BARRIER::Transition(**(this->pResource), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER)));

	/* Descriptor */

	this->Descriptor.BufferLocation = (*(this->pResource))->GetGPUVirtualAddress();
	this->Descriptor.SizeInBytes    = (this->vVertices.size() * sizeof(Vertex));
	this->Descriptor.StrideInBytes  = sizeof(Vertex);
}

Uniquis::DirectX12::VertexBuffer::VertexBuffer(const unsigned __int64                                   defaultHeapOffset,
										       const unsigned __int64                                   uploadHeapOffset,
										       const          std::vector<Vertex>                       vVertices, 
										       const          std::shared_ptr<Heap<HeapType::Default>>& ppDefaultHeap,
										       const          std::shared_ptr<Heap<HeapType::Upload>>&  ppUploadHeap,
										       const          CommandList&                              pCommandList, 
										       const          Device&                                   pDevice)

	:   Descriptor(),
	     vVertices(vVertices),
	  pDefaultHeap(ppDefaultHeap),
	   pUploadHeap(ppUploadHeap)
{
	/* Variables */

	SubresourceData Data = {};

	/* Descriptions */

	ResourceDescription<ResourceType::Buffer> VertexBufferDescription((this->vVertices.size() * sizeof(Vertex)), 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::COPY_DESTINATION, ResourceCreation::PLACED, ResourceFlags::NONE);

	Data.pData      = reinterpret_cast<BYTE*>(this->vVertices.data());
	Data.RowPitch   = (this->vVertices.size() * sizeof(Vertex));
	Data.SlicePitch = (this->vVertices.size() * sizeof(Vertex));

	/* Initialization */

	this->pResource = std::make_unique<Resource<ResourceType::Buffer>>(defaultHeapOffset, VertexBufferDescription, *(this->pDefaultHeap), pDevice);

	VertexBufferDescription.ResourceState = ResourceStates::GENERIC_READ;

	this->pUpload = std::make_unique<Resource<ResourceType::Buffer>>(uploadHeapOffset, VertexBufferDescription, *(this->pUploadHeap), pDevice);

	/* Update */

	UpdateSubresources(*(pCommandList), **(this->pResource), **(this->pUpload), 0, 0, 1, &(Data));

	pCommandList.transitionResource(*(this->pResource), ResourceStates::VERTEX_AND_CONSTANT_BUFFER);

	/* Descriptor */

	this->Descriptor.BufferLocation = (*(this->pResource))->GetGPUVirtualAddress();
	this->Descriptor.SizeInBytes    = (this->vVertices.size() * sizeof(Vertex));
	this->Descriptor.StrideInBytes  = sizeof(Vertex);
}

Uniquis::DirectX12::VertexBuffer::~VertexBuffer()
{

}

void Uniquis::DirectX12::VertexBuffer::update(const CommandList& pCommandList)
{
	BYTE* pVertexDataBegin;
	
	CD3DX12_RANGE ReadRange(0, 0); 
	
	(*(this->pUpload))->Map(0, &(ReadRange), reinterpret_cast<void**>(&(pVertexDataBegin)));
	
	memcpy(pVertexDataBegin, this->vVertices.data(), (this->vVertices.size() * sizeof(Vertex)));
	
	(*(this->pUpload))->Unmap(0, nullptr);
	
	pCommandList.transitionResource(*(this->pResource), ResourceStates::COPY_DESTINATION);
	
	pCommandList->CopyResource(**(this->pResource), **(this->pUpload));
	
	pCommandList.transitionResource(*(this->pResource), ResourceStates::VERTEX_AND_CONSTANT_BUFFER);
}

ID3D12Resource* Uniquis::DirectX12::VertexBuffer::operator*() const noexcept
{
	return (**(this->pResource));
}