#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Mesh.h"

template<Uniquis::DirectX12::TopologyTypes Type>
Uniquis::DirectX12::Mesh<Type>::Mesh(const Mesh& other)
{

}

template<Uniquis::DirectX12::TopologyTypes Type>
Uniquis::DirectX12::Mesh<Type>::Mesh(const std::vector<Vertex>           vVertices,
								const std::vector<unsigned __int32> vIndices,
								const CommandList&                  pCommandList, 
								const CommandQueue&                 pCommandQueue, 
								const Device&                       pDevice)

	: pVertexBuffer(),
	   pIndexBuffer()
{
	/* Variables */

	unsigned __int64 VertexBufferByteSize = (65536 * ((((vVertices.size() * sizeof(Vertex)) - ((vVertices.size() * sizeof(Vertex)) % 65536)) / 65536) + 1));

	unsigned __int64 IndexBufferByteSize = (65536 * ((((vIndices.size() * sizeof(unsigned __int32)) - ((vIndices.size() * sizeof(unsigned __int32)) % 65536)) / 65536) + 1));

	unsigned __int64 HeapByteSize = (VertexBufferByteSize + IndexBufferByteSize);

	/* Descriptions */

	HeapDescription<HeapType::Default> DefaultHeapDescription(65536, HeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	HeapDescription<HeapType::Upload> UploadHeapDescription(65536, HeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	/* Initialization */

	this->pDefaultHeap = std::make_shared<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);

	this->pUploadHeap = std::make_shared<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

	this->pVertexBuffer = std::make_unique<VertexBuffer>(0, 0, std::move(vVertices), this->pDefaultHeap, this->pUploadHeap, pCommandList, pDevice);

	this->pIndexBuffer = std::make_unique<IndexBuffer>(VertexBufferByteSize, VertexBufferByteSize, std::move(vIndices), this->pDefaultHeap, this->pUploadHeap, pCommandList, pDevice);
}

template<Uniquis::DirectX12::TopologyTypes Type>
Uniquis::DirectX12::Mesh<Type>::Mesh(const unsigned __int64                                    defaultHeapOffset,
								const unsigned __int64                                    uploadHeapOffset,
								const          std::vector<Vertex>                        vVertices,
								const          std::vector<unsigned __int32>              vIndices,
								const          std::shared_ptr<Heap<HeapType::Default>>& ppDefaultHeap,
								const          std::shared_ptr<Heap<HeapType::Upload>>&  ppUploadHeap,
								const          CommandList&                               pCommandList,
								const          CommandQueue&                              pCommandQueue,
								const          Device&                                    pDevice)
	: pVertexBuffer(),
	   pIndexBuffer()
{
	/* Variables */

	unsigned __int32 DataByteSize = (vVertices.size() * sizeof(Vertex));

	unsigned __int32 AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 VertexBufferByteSize = AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize;

	/* Initialization */

	this->pVertexBuffer = std::make_unique<VertexBuffer>(defaultHeapOffset, uploadHeapOffset, std::move(vVertices), ppDefaultHeap, ppUploadHeap, pCommandList, pDevice);

	this->pIndexBuffer = std::make_unique<IndexBuffer>((defaultHeapOffset + VertexBufferByteSize), (uploadHeapOffset + VertexBufferByteSize), std::move(vIndices), ppDefaultHeap, ppUploadHeap, pCommandList, pDevice);
}

template<Uniquis::DirectX12::TopologyTypes Type>
Uniquis::DirectX12::Mesh<Type>::~Mesh()
{

}

template<Uniquis::DirectX12::TopologyTypes Type>
void Uniquis::DirectX12::Mesh<Type>::render(const CommandList& pCommandList) const
{
	
}

template<>
void Uniquis::DirectX12::Mesh<Uniquis::DirectX12::TopologyTypes::POINT>::render(const CommandList& pCommandList) const
{
	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	pCommandList->IASetIndexBuffer(&(this->pIndexBuffer->Descriptor));
	pCommandList->IASetVertexBuffers(0, 1, &(this->pVertexBuffer->Descriptor));

	pCommandList->DrawIndexedInstanced(this->pIndexBuffer->vIndices.size(), 1, 0, 0, 0);
}

template<>
void Uniquis::DirectX12::Mesh<Uniquis::DirectX12::TopologyTypes::LINE>::render(const CommandList& pCommandList) const
{
	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	pCommandList->IASetIndexBuffer(&(this->pIndexBuffer->Descriptor));
	pCommandList->IASetVertexBuffers(0, 1, &(this->pVertexBuffer->Descriptor));

	pCommandList->DrawIndexedInstanced(this->pIndexBuffer->vIndices.size(), 1, 0, 0, 0);
}

template<>
void Uniquis::DirectX12::Mesh<Uniquis::DirectX12::TopologyTypes::TRIANGLE>::render(const CommandList& pCommandList) const
{
	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pCommandList->IASetIndexBuffer(&(this->pIndexBuffer->Descriptor));
	pCommandList->IASetVertexBuffers(0, 1, &(this->pVertexBuffer->Descriptor));

	pCommandList->DrawIndexedInstanced(this->pIndexBuffer->vIndices.size(), 1, 0, 0, 0);
}

template class Uniquis::DirectX12::Mesh<Uniquis::DirectX12::TopologyTypes::POINT>;
template class Uniquis::DirectX12::Mesh<Uniquis::DirectX12::TopologyTypes::LINE>;
template class Uniquis::DirectX12::Mesh<Uniquis::DirectX12::TopologyTypes::TRIANGLE>;
