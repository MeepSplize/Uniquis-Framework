#pragma once

#include "Device.h"
#include "CommandList.h"
#include "Heap.h"
#include "DescriptorHeap.h"
#include "ConstantBuffer.h"
#include "Mesh.h"
#include "..\\General\\Transformation.h"

namespace Uniquis::DirectX12
{
	class Model
	{
	public:

		unsigned __int8 cMeshes;

		std::vector<unsigned __int64> vStartIndices;

		std::vector<unsigned __int32> vIndices;
		std::vector<Vertex>           vVertices;

	public:

		Model() = delete;

		Model(const Model&) = delete;

		Model(const Model&&) = delete;

		Model(const std::wstring& pFilename);

		~Model();

	public:

		void operator=(const Model&) = delete;
	};
}