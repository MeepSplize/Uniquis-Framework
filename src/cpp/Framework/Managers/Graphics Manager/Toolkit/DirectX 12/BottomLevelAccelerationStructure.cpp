#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\BottomLevelAccelerationStructure.h"

Uniquis::DirectX12::BottomLevelAccelerationStructure::BottomLevelAccelerationStructure(const IndexBuffer& pIndexBuffer, 
																				  const VertexBuffer& pVertexBuffer, 
																				  const CommandList& pCommandList, 
																				  const Device& pDevice)
{
	pCommandList.transitionResource(*(pIndexBuffer.pResource),  ResourceStates::NON_PIXEL_SHADER_RESOURCE); // Todo: Put it in INDEX_BUFFER and NON_PIXEL_SHADER simultaniously
	pCommandList.transitionResource(*(pVertexBuffer.pResource), ResourceStates::NON_PIXEL_SHADER_RESOURCE); // -""- but with VERTEX_BUFFER

	/* Descriptions */

	D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE VertexBufferInformation = {};

	VertexBufferInformation.StartAddress  = (*(pVertexBuffer))->GetGPUVirtualAddress();
	VertexBufferInformation.StrideInBytes = 32; /* 16-Byte-Padding of Shaders might need to be considered */

	D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC RayTracingGeometryTrianglesDescription = {};
	
	RayTracingGeometryTrianglesDescription.Transform3x4 = 0;
	RayTracingGeometryTrianglesDescription.IndexFormat  = DXGI_FORMAT_R32_UINT;
	RayTracingGeometryTrianglesDescription.VertexFormat = DXGI_FORMAT_R32G32B32_FLOAT;
	RayTracingGeometryTrianglesDescription.IndexCount   = pIndexBuffer.vIndices.size();
	RayTracingGeometryTrianglesDescription.VertexCount  = pVertexBuffer.vVertices.size();
	RayTracingGeometryTrianglesDescription.IndexBuffer  = (*(pIndexBuffer))->GetGPUVirtualAddress();
	RayTracingGeometryTrianglesDescription.VertexBuffer = VertexBufferInformation;

	D3D12_RAYTRACING_GEOMETRY_DESC RayTracingGeometryDescription = {};

	RayTracingGeometryDescription.Type      = D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES;
	RayTracingGeometryDescription.Flags     = D3D12_RAYTRACING_GEOMETRY_FLAG_NONE; /* D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE */
	RayTracingGeometryDescription.Triangles = RayTracingGeometryTrianglesDescription;

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS BottomLevelAccelerationStructureInputDescription = {};

	BottomLevelAccelerationStructureInputDescription.Type           = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL;
	BottomLevelAccelerationStructureInputDescription.Flags          = D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE;
	BottomLevelAccelerationStructureInputDescription.NumDescs       = 1;
	BottomLevelAccelerationStructureInputDescription.DescsLayout    = D3D12_ELEMENTS_LAYOUT_ARRAY;
	BottomLevelAccelerationStructureInputDescription.pGeometryDescs = &(RayTracingGeometryDescription);

	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO PrebuildInfo = {};

	pDevice->GetRaytracingAccelerationStructurePrebuildInfo(&(BottomLevelAccelerationStructureInputDescription), &(PrebuildInfo));

	unsigned __int64 DataByteSize  = PrebuildInfo.ScratchDataSizeInBytes;
	unsigned __int64 AlignmentRest = (DataByteSize % 256);

	unsigned __int64 ScratchMemoryByteSize = (AlignmentRest ? (DataByteSize + (256 - AlignmentRest)) : DataByteSize);
	
	DataByteSize  = PrebuildInfo.ResultDataMaxSizeInBytes;
	AlignmentRest = (DataByteSize % 256);

	unsigned __int64 InternalStructureByteSize = (AlignmentRest ? (DataByteSize + (256 - AlignmentRest)) : DataByteSize);

	DataByteSize  = ScratchMemoryByteSize;
	AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 ScratchMemoryHeapByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	DataByteSize  = InternalStructureByteSize;
	AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 InternalStructureHeapByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	unsigned __int64 HeapByteSize = (ScratchMemoryHeapByteSize + InternalStructureHeapByteSize);

	HeapDescription<HeapType::Default> HeapDescription(65536, HeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	ResourceDescription<ResourceType::Buffer> ScratchResourceDescription(ScratchMemoryByteSize, 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::COMMON, ResourceCreation::PLACED, ResourceFlags::ALLOW_UNORDERED_ACCESS);

	ResourceDescription<ResourceType::Buffer> InternalStructureResourceDescription(InternalStructureByteSize, 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::RAYTRACING_ACCELERATION_STRUCTURE, ResourceCreation::PLACED, ResourceFlags::ALLOW_UNORDERED_ACCESS);
	
	/* Resource Initialization */

	this->pHeap = std::make_unique<Heap<HeapType::Default>>(HeapDescription, pDevice);

	this->pScratchResource = std::make_unique<Resource<ResourceType::Buffer>>(0, ScratchResourceDescription, *(this->pHeap), pDevice);

	this->pInternalStructureResource = std::make_unique<Resource<ResourceType::Buffer>>(ScratchMemoryHeapByteSize, InternalStructureResourceDescription, *(this->pHeap), pDevice);

	/* Bottom Level Acceleration Structure Generation */

	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC BottomLevelAccelerationStructureBuildDescription = {};

	BottomLevelAccelerationStructureBuildDescription.DestAccelerationStructureData    = (*(this->pInternalStructureResource))->GetGPUVirtualAddress();
	BottomLevelAccelerationStructureBuildDescription.Inputs                           = BottomLevelAccelerationStructureInputDescription;
	BottomLevelAccelerationStructureBuildDescription.SourceAccelerationStructureData  = 0;
	BottomLevelAccelerationStructureBuildDescription.ScratchAccelerationStructureData = (*(this->pScratchResource))->GetGPUVirtualAddress();

	pCommandList->BuildRaytracingAccelerationStructure(&(BottomLevelAccelerationStructureBuildDescription), 0, nullptr);
}

Uniquis::DirectX12::BottomLevelAccelerationStructure::~BottomLevelAccelerationStructure()
{

}