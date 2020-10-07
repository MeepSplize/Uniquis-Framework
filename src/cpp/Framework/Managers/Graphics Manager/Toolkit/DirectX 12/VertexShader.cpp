#include "pch.h"

#include "Project\\Macros\\Macros.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\VertexShader.h"

Uniquis::DirectX12::VertexShader::VertexShader(const wchar_t* fileName)

	: ShaderBytecode{ nullptr, 0 }, pShaderBytecode(nullptr), FileName(fileName), Flags1(NULL), Flags2(NULL) 
{
	this->pShaderBytecode = &(this->ShaderBytecode);

	#ifdef _DEBUG

		this->Flags1 = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	#endif
}

void Uniquis::DirectX12::VertexShader::compile()
{
	HRESULT hResult;

	std::wstring FilePath = L"";

	hResult = D3DCompileFromFile(FilePath.append(VS_PATH).append(this->FileName).append(L".hlsl").c_str(), 
								 nullptr, 
								 nullptr, 
								 "main", 
								 "vs_5_1", 
								 this->Flags1, 
								 this->Flags2, 
								 &(this->pShaderBlob), 
								 &(this->pError));

	if (FAILED(hResult)) 
	{
		OutputDebugString(L"[ERROR] Failed compiling Vertex Shader \n");

		OutputDebugStringA((char*) this->pError->GetBufferPointer());
		this->pError->Release();
	}

	this->ShaderBytecode.pShaderBytecode = this->pShaderBlob.Get()->GetBufferPointer();
	this->ShaderBytecode.BytecodeLength  = this->pShaderBlob.Get()->GetBufferSize();
}

D3D12_SHADER_BYTECODE Uniquis::DirectX12::VertexShader::operator*() const noexcept
{
	return this->ShaderBytecode;
}

D3D12_SHADER_BYTECODE* Uniquis::DirectX12::VertexShader::operator->() const noexcept
{
	return this->pShaderBytecode;
}