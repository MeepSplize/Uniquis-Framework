#pragma once

#include <WRL.h>

namespace Uniquis::DirectX12
{
	class PixelShader
	{

	// VARIABLES

	private:

		Microsoft::WRL::ComPtr<ID3DBlob> pShaderBlob;

		Microsoft::WRL::ComPtr<ID3DBlob> pError;

		D3D12_SHADER_BYTECODE   ShaderBytecode;
		D3D12_SHADER_BYTECODE* pShaderBytecode;

		const wchar_t* FileName;

	public:

		unsigned __int32 CompileFlags;

	// CONSTRUCTORS

	public:

		PixelShader(const wchar_t* fileName);

	// DECONSTRUCTORS

	public:

		~PixelShader() = default;

	// FUNCTIONS

	public:

		void compile();

	// OPERATORS

	public:

		D3D12_SHADER_BYTECODE  operator*()  const noexcept;
		D3D12_SHADER_BYTECODE* operator->() const noexcept;
	};
}