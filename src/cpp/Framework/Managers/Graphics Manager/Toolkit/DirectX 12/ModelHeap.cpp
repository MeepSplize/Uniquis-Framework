#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\ModelHeap.h"

Uniquis::DirectX12::ModelHeap::ModelHeap(const unsigned __int64 heapByteSize,
									     const          Device& pDevice)

	: ByteCapacity(0, heapByteSize)
{
	HeapDescription<HeapType::Upload> UploadHeapDescription(65536, heapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	HeapDescription<HeapType::Default> DefaultHeapDescription(65536, heapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	this->pUploadHeap = std::make_shared<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

	this->pDefaultHeap = std::make_shared<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);
}

Uniquis::DirectX12::ModelHeap::~ModelHeap()
{

}

void Uniquis::DirectX12::ModelHeap::add(const std::wstring& pFilename,
				                        const CommandList&  pCommandList,
				                        const Device&       pDevice)
{
	std::wifstream InputFileStream(pFilename.c_str());

	if ((InputFileStream.get() == L'i') && (InputFileStream.get() == L'd'))
	{
		InputFileStream.get();

		std::wstring Result;

		wchar_t Character = L' ';

		while (Character != L'\n')
		{
			Result.push_back(Character);

			Character = InputFileStream.get();
		}

		this->vModelIDs.push_back(std::stoi(Result));
	}

	/* Scene Processing */

	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(std::move(std::string(pFilename.begin(), pFilename.end())),
											  
											  //aiProcess_MakeLeftHanded        |
											  aiProcess_FindInvalidData       |
											  //aiProcess_GenSmoothNormals      |
											  //aiProcess_FixInfacingNormals    |
											  //aiProcess_FlipWindingOrder      |
											  //aiProcess_FlipUVs               |
                                              //aiProcess_CalcTangentSpace      |
                                              aiProcess_Triangulate           |
                                              aiProcess_JoinIdenticalVertices |
                                              aiProcess_SortByPType           |
											  aiProcess_ValidateDataStructure |
											  //aiProcess_FlipUVs               |
											  aiProcess_ImproveCacheLocality);

	if (!(pScene))
	{
		OutputDebugStringA(Importer.GetErrorString());
	
		OutputDebugString(L"\n");
	}

	std::vector<Vertex> vVertices;

	std::vector<Vector<3>> vPositions;
	std::vector<Vector<3>> vNormals;
	std::vector<Vector<2>> vTextureCoordinates;

	std::vector<unsigned __int32>  vIndices;

	std::array<float, 3> vTempStorage;

	for (unsigned __int16 i = 0; i < pScene->mNumMeshes; i++)
	{
		/* Positions */

		if (pScene->mMeshes[i]->HasPositions())
		{
			vPositions.reserve(pScene->mMeshes[i]->mNumVertices);

			for (unsigned __int32 j = 0; j < pScene->mMeshes[i]->mNumVertices; j++)
			{
				vTempStorage[0] = pScene->mMeshes[i]->mVertices[j].x;
				vTempStorage[1] = pScene->mMeshes[i]->mVertices[j].y;
				vTempStorage[2] = pScene->mMeshes[i]->mVertices[j].z;

				vPositions.emplace_back(vTempStorage.data());
			}
		}
		
		/* Normals */

		if (pScene->mMeshes[i]->HasNormals())
		{
			vNormals.reserve(pScene->mMeshes[0]->mNumVertices);

			for (unsigned __int32 j = 0; j < pScene->mMeshes[i]->mNumVertices; j++)
			{
				vTempStorage[0] = pScene->mMeshes[i]->mNormals[j].x;
				vTempStorage[1] = pScene->mMeshes[i]->mNormals[j].y;
				vTempStorage[2] = pScene->mMeshes[i]->mNormals[j].z;

				vNormals.emplace_back(vTempStorage.data());
			}
		}

		if (pScene->mMeshes[i]->HasTextureCoords(0))
		{
			vTextureCoordinates.reserve(pScene->mMeshes[0]->mNumVertices);

			for (unsigned __int32 j = 0; j < pScene->mMeshes[i]->mNumVertices; j++)
			{
				vTempStorage[0] = pScene->mMeshes[i]->mTextureCoords[0][j].x;
				vTempStorage[1] = pScene->mMeshes[i]->mTextureCoords[0][j].y;

				vTextureCoordinates.emplace_back(vTempStorage.data());
			}
		}
		else
		{
			__debugbreak();
		}

		/* Indices */

		if (pScene->mMeshes[i]->HasFaces())
		{
			vIndices.reserve(3 * pScene->mMeshes[0]->mNumFaces);
			
			for (unsigned __int32 j = 0; j < pScene->mMeshes[i]->mNumFaces; j++)
			{
				for (unsigned __int32 k = 0; k < 3; k++)
				{
					vIndices.emplace_back(pScene->mMeshes[i]->mFaces[j].mIndices[k]);
				}
			}
		}
	}

	//aiNodeAnim* pNodeAnim = pScene->mAnimations[0]->mChannels[0];

	//if (pNodeAnim->mNodeName == L"TestObject (oder so)") -> Jo, Animation gehört zum geladenen Object und so

	/* Vertices */

	vVertices.reserve(vPositions.size());

	for (unsigned __int32 i = 0; i < vPositions.size(); i++)
	{
		vVertices.emplace_back(std::move(vPositions[i]), std::move(vNormals[i]), std::move(vTextureCoordinates[i]));
	}

	/* Variables */

	unsigned __int64 DataByteSize  = (vVertices.size() * sizeof(Vertex));
	unsigned __int64 AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 VertexBufferHeapByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	DataByteSize  = (vIndices.size() * sizeof(unsigned __int32));
	AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 IndexBufferByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	unsigned __int64 HeapByteSize = (VertexBufferHeapByteSize + IndexBufferByteSize);

	/* Initialization */

	this->vpIndexBuffers.emplace_back(std::make_unique<IndexBuffer>((VertexBufferHeapByteSize + this->ByteCapacity.first), (VertexBufferHeapByteSize + this->ByteCapacity.first), std::move(vIndices), this->pDefaultHeap, this->pUploadHeap, pCommandList, pDevice));

	this->vpVertexBuffers.emplace_back(std::make_unique<VertexBuffer>(this->ByteCapacity.first, this->ByteCapacity.first, std::move(vVertices), this->pDefaultHeap, this->pUploadHeap, pCommandList, pDevice));

	this->ByteCapacity.first += HeapByteSize;
}

void Uniquis::DirectX12::ModelHeap::add(Model& pModel)
{

}

void Uniquis::DirectX12::ModelHeap::add(const unsigned __int32 modelID, std::vector<unsigned __int32> vIndices, std::vector<Vertex> vVertices, const CommandList& pCommandList, const Device& pDevice)
{
	/* Variables */

	unsigned __int64 DataByteSize  = (vVertices.size() * sizeof(Vertex));
	unsigned __int64 AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 VertexBufferHeapByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	DataByteSize  = (vIndices.size() * sizeof(unsigned __int32));
	AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 IndexBufferByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	unsigned __int64 HeapByteSize = (VertexBufferHeapByteSize + IndexBufferByteSize);

	/* Initialization */

	this->vpIndexBuffers.emplace_back(std::make_unique<IndexBuffer>((VertexBufferHeapByteSize + this->ByteCapacity.first), (VertexBufferHeapByteSize + this->ByteCapacity.first), std::move(vIndices), this->pDefaultHeap, this->pUploadHeap, pCommandList, pDevice));

	this->vpVertexBuffers.emplace_back(std::make_unique<VertexBuffer>(this->ByteCapacity.first, this->ByteCapacity.first, std::move(vVertices), this->pDefaultHeap, this->pUploadHeap, pCommandList, pDevice));

	this->ByteCapacity.first += HeapByteSize;

	this->vModelIDs.push_back(modelID);
}