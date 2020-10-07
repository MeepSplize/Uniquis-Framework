#pragma once

#include <WRL.h>

namespace Uniquis::DirectX12
{
	class VertexShader
	{
	private:

		Microsoft::WRL::ComPtr<ID3DBlob> pShaderBlob;

		Microsoft::WRL::ComPtr<ID3DBlob> pError;

		D3D12_SHADER_BYTECODE   ShaderBytecode;
		D3D12_SHADER_BYTECODE* pShaderBytecode;

		const wchar_t* FileName;

	public:

		unsigned __int32 Flags1;
		unsigned __int32 Flags2;

	public:

		VertexShader(const wchar_t* fileName);

		~VertexShader() = default;

	public:

		void compile();

	public:

		D3D12_SHADER_BYTECODE  operator*()  const noexcept;
		D3D12_SHADER_BYTECODE* operator->() const noexcept;
	};
}