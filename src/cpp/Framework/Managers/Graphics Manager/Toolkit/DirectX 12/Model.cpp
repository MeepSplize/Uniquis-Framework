#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Model.h"

Uniquis::DirectX12::Model::Model(const std::wstring& pFilename)

	: cMeshes(0)
{
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
		this->cMeshes++;

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

		/* Indices */

		if (pScene->mMeshes[i]->HasFaces())
		{
			this->vStartIndices.emplace_back(vIndices.size());

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

	/* Vertices */

	vVertices.reserve(vPositions.size());

	for (unsigned __int32 i = 0; i < vPositions.size(); i++)
	{
		vVertices.emplace_back(std::move(vPositions[i]), std::move(vNormals[i]), Vector<2>( { 0.0f, 0.0f } ));
	}
}

Uniquis::DirectX12::Model::~Model()
{

}