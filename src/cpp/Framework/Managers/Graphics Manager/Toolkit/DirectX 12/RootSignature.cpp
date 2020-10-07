#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\RootSignature.h"

Uniquis::DirectX12::RootSignature::RootSignature(const RootSignatureDescription& pDescription, 
											     const Device&                   pDevice)
{
	HRESULT hResult;

	hResult = D3D12SerializeVersionedRootSignature(&(pDescription.InternalDescription),
												   &(this->pRootSignatureBlob),
												   &(this->pError));

	if (FAILED(hResult))
	{
		OutputDebugString(L"[ERROR] Failed to serialize RootSignature \n");

		_com_error ComError(hResult);
		
		LPCTSTR ComErrorMessage = ComError.ErrorMessage();

		OutputDebugString(std::wstring(L"HRESULT: ").append(ComErrorMessage).append(L"\n").c_str());

		OutputDebugStringA(std::string("Message: ").append(reinterpret_cast<char*>(this->pError->GetBufferPointer())).append("\n").c_str());

        this->pError->Release();
	}

	if (FAILED(pDevice->CreateRootSignature(0,
										    this->pRootSignatureBlob->GetBufferPointer(),
										    this->pRootSignatureBlob->GetBufferSize(),
										    IID_PPV_ARGS(&(this->pRootSignature)))))
	{
		OutputDebugString(L"[ERROR] Failed to create Root Signature! \n");
	}
}

Uniquis::DirectX12::RootSignature::~RootSignature()
{
	this->pRootSignature->Release();

	this->pRootSignatureBlob->Release();
}

ID3D12RootSignature* Uniquis::DirectX12::RootSignature::operator*() const 
{
	return this->pRootSignature;
}

ID3D12RootSignature* Uniquis::DirectX12::RootSignature::operator->() const
{
	return this->pRootSignature;
}