#include "pch.h"

#include "Project\\Macros\\Macros.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\GeometryShader.h"

Uniquis::DirectX12::GeometryShader::GeometryShader(const wchar_t* fileName)

	: ShaderBytecode{ nullptr, 0 }, pShaderBytecode(nullptr), FileName(fileName), Flags1(NULL), Flags2(NULL) 
{
	this->pShaderBytecode = &(this->ShaderBytecode);

	#ifdef _DEBUG

		this->Flags1 = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	#endif
}

void Uniquis::DirectX12::GeometryShader::compile()
{
	std::wstring FilePath(GS_PATH);

	if (FAILED(D3DCompileFromFile(FilePath.append(this->FileName).append(L".hlsl").c_str(), 
								  nullptr, 
								  nullptr, 
								  "main", 
								  "gs_5_1", 
								  this->Flags1, 
								  this->Flags2, 
								  &(this->pShaderBlob), 
								  &(this->pError)))) 
	{
		OutputDebugString(L"[ERROR] Failed compiling Geometry Shader \n");

		OutputDebugStringA((char*) this->pError->GetBufferPointer());

		this->pError->Release();
	}

	this->ShaderBytecode.pShaderBytecode = this->pShaderBlob.Get()->GetBufferPointer();
	this->ShaderBytecode.BytecodeLength  = this->pShaderBlob.Get()->GetBufferSize();
}

D3D12_SHADER_BYTECODE Uniquis::DirectX12::GeometryShader::operator*() const noexcept
{
	return this->ShaderBytecode;
}

D3D12_SHADER_BYTECODE* Uniquis::DirectX12::GeometryShader::operator->() const noexcept
{
	return this->pShaderBytecode;
}