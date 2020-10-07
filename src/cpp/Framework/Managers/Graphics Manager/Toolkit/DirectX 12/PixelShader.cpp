#include "pch.h"

#include "Project\\Macros\\Macros.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\PixelShader.h"

Uniquis::DirectX12::PixelShader::PixelShader(const wchar_t* fileName)

	:  ShaderBytecode{ nullptr, 0 }, 
	  pShaderBytecode(nullptr), 
	         FileName(fileName), 
	     CompileFlags(0) 
{
	this->pShaderBytecode = &(this->ShaderBytecode);

#ifdef _DEBUG

	this->CompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

#endif
}

void Uniquis::DirectX12::PixelShader::compile() 
{
	std::wstring FilePath;

	if (FAILED(D3DCompileFromFile(FilePath.append(PS_PATH).append(this->FileName).append(L".hlsl").c_str(),
								  nullptr, 
								  nullptr, 
								  "main", 
								  "ps_5_1", 
								  this->CompileFlags, 
								  NULL, 
								  &(this->pShaderBlob), 
								  &(this->pError))))
	{
		OutputDebugString(L"[ERROR] Failed compiling Vertex Shader \n");

		OutputDebugStringA((char*) this->pError->GetBufferPointer());

		this->pError->Release();
	}

	this->ShaderBytecode.pShaderBytecode = this->pShaderBlob.Get()->GetBufferPointer();
	this->ShaderBytecode.BytecodeLength  = this->pShaderBlob.Get()->GetBufferSize();
}

D3D12_SHADER_BYTECODE Uniquis::DirectX12::PixelShader::operator*() const noexcept
{
	return this->ShaderBytecode;
}

D3D12_SHADER_BYTECODE* Uniquis::DirectX12::PixelShader::operator->() const noexcept
{
	return this->pShaderBytecode;
}