#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\TopLevelAccelerationStructure.h"

Uniquis::DirectX12::TopLevelAccelerationStructure::TopLevelAccelerationStructure(const BottomLevelAccelerationStructure* pBottomLevelAccelerationStructure,
																			 const CommandList&                      pCommandList, 
																			 const Device&                           pDevice)
{
	unsigned __int16 cInstances = 1;

	/* Descriptions */

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS InputDescription = {};

	InputDescription.Type          = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL;
	InputDescription.Flags         = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
	InputDescription.NumDescs      = cInstances;
	InputDescription.DescsLayout   = D3D12_ELEMENTS_LAYOUT_ARRAY;

	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO PrebuildInfo = {};

	pDevice->GetRaytracingAccelerationStructurePrebuildInfo(&(InputDescription), &(PrebuildInfo));

	unsigned __int64 DataByteSize  = PrebuildInfo.ScratchDataSizeInBytes;
	unsigned __int64 AlignmentRest = (DataByteSize % 256);

	unsigned __int64 ScratchMemoryByteSize = (AlignmentRest ? (DataByteSize + (256 - AlignmentRest)) : DataByteSize);
	
	DataByteSize  = PrebuildInfo.ResultDataMaxSizeInBytes;
	AlignmentRest = (DataByteSize % 256);

	unsigned __int64 InternalStructureByteSize = (AlignmentRest ? (DataByteSize + (256 - AlignmentRest)) : DataByteSize);

	 DataByteSize  = (cInstances * sizeof(D3D12_RAYTRACING_INSTANCE_DESC));
	 AlignmentRest = (DataByteSize % 256);

	unsigned __int64 InstanceDescriptionsByteSize = (AlignmentRest ? (DataByteSize + (256 - AlignmentRest)) : DataByteSize);

	DataByteSize  = ScratchMemoryByteSize;
	AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 ScratchMemoryHeapByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	DataByteSize  = InternalStructureByteSize;
	AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 InternalStructureHeapByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	DataByteSize  = InstanceDescriptionsByteSize;
	AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 InstanceDescriptionsHeapByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	unsigned __int64 DefaultHeapByteSize = (ScratchMemoryHeapByteSize + InternalStructureHeapByteSize);

	HeapDescription<HeapType::Default> DefaultHeapDescription(65536, DefaultHeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	HeapDescription<HeapType::Upload> UploadHeapDescription(65536, InstanceDescriptionsHeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	ResourceDescription<ResourceType::Buffer> ScratchMemoryResourceDescription(ScratchMemoryByteSize, 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::UNORDERED_ACCESS, ResourceCreation::PLACED, ResourceFlags::ALLOW_UNORDERED_ACCESS);

	ResourceDescription<ResourceType::Buffer> InternalStructureResourceDescription(InternalStructureByteSize, 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::RAYTRACING_ACCELERATION_STRUCTURE, ResourceCreation::PLACED, ResourceFlags::ALLOW_UNORDERED_ACCESS);

	ResourceDescription<ResourceType::Buffer> InstanceDescriptionsResourceDescription(InstanceDescriptionsByteSize, 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::GENERIC_READ, ResourceCreation::PLACED, ResourceFlags::NONE);
	
	/* Resource Initialization */

	this->pDefaultHeap = std::make_unique<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);

	this->pUploadHeap = std::make_unique<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

	this->pScratchResource = std::make_unique<Resource<ResourceType::Buffer>>(0, ScratchMemoryResourceDescription, *(this->pDefaultHeap), pDevice);

	this->pInternalStructureResource = std::make_unique<Resource<ResourceType::Buffer>>(ScratchMemoryHeapByteSize, InternalStructureResourceDescription, *(this->pDefaultHeap), pDevice);

	this->pInstanceDescriptionsResource = std::make_unique<Resource<ResourceType::Buffer>>(0, InstanceDescriptionsResourceDescription, *(this->pUploadHeap), pDevice);

	/* Generation */

	D3D12_RAYTRACING_INSTANCE_DESC* pInstanceDescription;

	(*(this->pInstanceDescriptionsResource))->Map(0, nullptr, reinterpret_cast<void **>(&(pInstanceDescription)));

	float Matrix[3][4] = {

		{ { 1 }, { 0 }, { 0 }, { 0 } },
		{ { 0 }, { 1 }, { 0 }, { 0 } },
		{ { 0 }, { 0 }, { 1 }, { 0 } }
	};

	for (unsigned __int16 i = 0; i < cInstances; i++)
	{
		pInstanceDescription[i].InstanceID                          = 0;
		pInstanceDescription[i].InstanceMask                        = 0xFF;
		pInstanceDescription[i].InstanceContributionToHitGroupIndex = 0;
		pInstanceDescription[i].Flags                               = D3D12_RAYTRACING_INSTANCE_FLAG_NONE;
		pInstanceDescription[i].AccelerationStructure               = (*(pBottomLevelAccelerationStructure->pInternalStructureResource))->GetGPUVirtualAddress();

		memcpy(&(pInstanceDescription[i].Transform), &(Matrix[0][0]), sizeof(pInstanceDescription[i].Transform));
	}

	(*(this->pInstanceDescriptionsResource))->Unmap(0, nullptr);

	InputDescription.InstanceDescs = (*(this->pInstanceDescriptionsResource))->GetGPUVirtualAddress();

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC BuildDescription = {};

	BuildDescription.DestAccelerationStructureData    = (*(this->pInternalStructureResource))->GetGPUVirtualAddress();
	BuildDescription.Inputs                           = InputDescription;
	BuildDescription.SourceAccelerationStructureData  = 0;
	BuildDescription.ScratchAccelerationStructureData = (*(this->pScratchResource))->GetGPUVirtualAddress();

	pCommandList->BuildRaytracingAccelerationStructure(&(BuildDescription), 0, nullptr);

	D3D12_RESOURCE_BARRIER UAVBarrier = {};

	UAVBarrier.Type          = D3D12_RESOURCE_BARRIER_TYPE_UAV;
	UAVBarrier.UAV.pResource = **(this->pInternalStructureResource);
	UAVBarrier.Flags         = D3D12_RESOURCE_BARRIER_FLAG_NONE;

	pCommandList->ResourceBarrier(1, &(UAVBarrier));
}

Uniquis::DirectX12::TopLevelAccelerationStructure::~TopLevelAccelerationStructure()
{

}