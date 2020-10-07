#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\ConstantBuffer.h"

Uniquis::DirectX12::ConstantBuffer::ConstantBuffer(const unsigned __int32                                               cConstants, 
											                     DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
											       const         CommandList&                                           pCommandList, 
											       const         Device&                                                pDevice)

	: vData()
{
	this->vData.reserve(cConstants);

	for (unsigned __int32 i = 0; i < cConstants; i++)
	{
		this->vData.emplace_back();
	}

	/* Variables */

	SubresourceData Data = {};

	/* Descriptions */

	ResourceDescription<ResourceType::Buffer> ResourceDescription((this->vData.size() * sizeof(float)), 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::COPY_DESTINATION, ResourceCreation::PLACED, ResourceFlags::NONE);

	Data.pData      = reinterpret_cast<BYTE*>(this->vData.data());
	Data.RowPitch   = (this->vData.size() * sizeof(float));
	Data.SlicePitch = (this->vData.size() * sizeof(float));

	unsigned __int32 DataByteSize = (this->vData.size() * sizeof(float));

	unsigned __int32 AlignmentRest = (DataByteSize % 65536);

	const unsigned __int32 HeapByteSize = AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize;

	HeapDescription<HeapType::Default> DefaultHeapDescription(65536, HeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	HeapDescription<HeapType::Upload> UploadHeapDescription(65536, HeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	/* Initialization */

	this->pDefaultHeap = std::make_shared<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);

	(*(this->pDefaultHeap))->SetName(L"DEFAULT HEAP FOR CONSTANT BUFFER");
	
	this->pUploadHeap = std::make_shared<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

	(*(this->pUploadHeap))->SetName(L"UPLOAD HEAP FOR CONSTANT BUFFER");

	this->pResource = std::make_unique<Resource<ResourceType::Buffer>>(0, ResourceDescription, *(this->pDefaultHeap), pDevice);

	(*(this->pResource))->SetName(L"DEFAULT RESOURCE FOR CONSTANT BUFFER");

	ResourceDescription.ResourceState = ResourceStates::GENERIC_READ;

	this->pUpload = std::make_unique<Resource<ResourceType::Buffer>>(0, ResourceDescription, *(this->pUploadHeap), pDevice);

	(*(this->pUpload))->SetName(L"UPLOAD RESOURCE FOR CONSTANT BUFFER");

	/* Update */

	UpdateSubresources(*(pCommandList), **(this->pResource), **(this->pUpload), 0, 0, 1, &(Data));

	pCommandList.transitionResource(*(this->pResource), ResourceStates::VERTEX_AND_CONSTANT_BUFFER);

	/* Descriptor */
	
	AlignmentRest = (DataByteSize % 256);

	this->DescriptorDescription.BufferLocation = (*(this->pResource))->GetGPUVirtualAddress();
	this->DescriptorDescription.SizeInBytes    = AlignmentRest ? (DataByteSize + (256 - AlignmentRest)) : DataByteSize;
}

Uniquis::DirectX12::ConstantBuffer::ConstantBuffer(const std::vector<float>                                     vData, 
											             DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
											       const CommandList&                                           pCommandList, 
											       const Device&                                                pDevice)

	: vData(vData)
{
	/* Variables */

	SubresourceData Data = {};

	/* Descriptions */

	ResourceDescription<ResourceType::Buffer> ResourceDescription((vData.size() * sizeof(float)), 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::COPY_DESTINATION, ResourceCreation::PLACED, ResourceFlags::NONE);

	Data.pData      = reinterpret_cast<BYTE*>(this->vData.data());
	Data.RowPitch   = (this->vData.size() * sizeof(float));
	Data.SlicePitch = (this->vData.size() * sizeof(float));

	unsigned __int32 DataByteSize = (this->vData.size() * sizeof(float));

	unsigned __int32 AlignmentRest = (DataByteSize % 65536);

	const unsigned __int32 HeapByteSize = AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize;

	HeapDescription<HeapType::Default> DefaultHeapDescription(65536, HeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	HeapDescription<HeapType::Upload> UploadHeapDescription(65536, HeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	/* Initialization */

	this->pDefaultHeap = std::make_shared<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);

	(*(this->pDefaultHeap))->SetName(L"DEFAULT HEAP FOR CONSTANT BUFFER");
	
	this->pUploadHeap = std::make_shared<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

	(*(this->pUploadHeap))->SetName(L"UPLOAD HEAP FOR CONSTANT BUFFER");

	this->pResource = std::make_unique<Resource<ResourceType::Buffer>>(0, ResourceDescription, *(this->pDefaultHeap), pDevice);

	(*(this->pResource))->SetName(L"DEFAULT RESOURCE FOR CONSTANT BUFFER");

	ResourceDescription.ResourceState = ResourceStates::GENERIC_READ;

	this->pUpload = std::make_unique<Resource<ResourceType::Buffer>>(0, ResourceDescription, *(this->pUploadHeap), pDevice);

	(*(this->pUpload))->SetName(L"UPLOAD RESOURCE FOR CONSTANT BUFFER");

	/* Update */

	UpdateSubresources(*(pCommandList), **(this->pResource), **(this->pUpload), 0, 0, 1, &(Data));

	pCommandList.transitionResource(*(this->pResource), ResourceStates::VERTEX_AND_CONSTANT_BUFFER);

	/* Descriptor */
	
	AlignmentRest = (DataByteSize % 256);

	this->DescriptorDescription.BufferLocation = (*(this->pResource))->GetGPUVirtualAddress();
	this->DescriptorDescription.SizeInBytes    = AlignmentRest ? (DataByteSize + (256 - AlignmentRest)) : DataByteSize;
}

Uniquis::DirectX12::ConstantBuffer::~ConstantBuffer()
{

}

void Uniquis::DirectX12::ConstantBuffer::bind(const unsigned __int32                                                iPartition,
			                                                 DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			                                  const          Device&                                                pDevice)
{
	pDescriptorHeap.addDescriptor(iPartition, this->DescriptorDescription, pDevice);
}

void Uniquis::DirectX12::ConstantBuffer::update(const CommandList& pCommandList)
{
	BYTE* pDataBegin;
	
	CD3DX12_RANGE ReadRange(0, 0); 
	
	(*(this->pUpload))->Map(0, &(ReadRange), reinterpret_cast<void**>(&(pDataBegin)));
	
	memcpy(pDataBegin, this->vData.data(), (this->vData.size() * sizeof(float)));
	
	(*(this->pUpload))->Unmap(0, nullptr);
	
	pCommandList.transitionResource(*(this->pResource), ResourceStates::COPY_DESTINATION);
	
	pCommandList->CopyResource(**(this->pResource), **(this->pUpload));
	
	pCommandList.transitionResource(*(this->pResource), ResourceStates::VERTEX_AND_CONSTANT_BUFFER);
}