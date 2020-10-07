#pragma once

#include "Toolkit\\Math\\Quaternion.h"
#include "Toolkit\\Math\\Vector.h"

#include "Toolkit\\Geometry\\Box.h"
#include "Toolkit\\Geometry\\Square.h"
#include "Toolkit\\Geometry\\Point.h"

#include "Types.h"

#include "Device.h"
#include "CommandQueue.h"
#include "CommandList.h"
#include "Heap.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Vertex.h"

namespace Uniquis::DirectX12
{
	template<TopologyTypes Type>
	class Mesh
	{
	private:

		std::shared_ptr<Heap<HeapType::Default>> pDefaultHeap;
		std::shared_ptr<Heap<HeapType::Upload>>  pUploadHeap;

	public:

		std::unique_ptr<VertexBuffer> pVertexBuffer;
		std::unique_ptr<IndexBuffer>  pIndexBuffer;

	public:

		Mesh(const Mesh& other);

		Mesh(const std::vector<Vertex>           vVertices,
			 const std::vector<unsigned __int32> vIndices,
			 const CommandList&                  pCommandList, 
			 const CommandQueue&                 pCommandQueue, 
			 const Device&                       pDevice);

		Mesh(const unsigned __int64                                    defaultHeapOffset,
			 const unsigned __int64                                    uploadHeapOffset,
			 const          std::vector<Vertex>                        vVertices,
			 const          std::vector<unsigned __int32>              vIndices,
			 const          std::shared_ptr<Heap<HeapType::Default>>& ppDefaultHeap,
			 const          std::shared_ptr<Heap<HeapType::Upload>>&  ppUploadHeap,
			 const          CommandList&                               pCommandList, 
			 const          CommandQueue&                              pCommandQueue, 
			 const          Device&                                    pDevice);

	public:

		~Mesh();

	public:

		void render(const CommandList& pCommandList) const;
	};
}