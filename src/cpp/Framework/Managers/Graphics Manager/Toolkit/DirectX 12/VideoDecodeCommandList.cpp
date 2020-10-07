#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\VideoDecodeCommandList.h"

Uniquis::DirectX12::VideoDecodeCommandList::VideoDecodeCommandList(const CommandList& pCommandList)
{
	pCommandList->QueryInterface(__uuidof(ID3D12VideoDecodeCommandList1), reinterpret_cast<void**>(&(this->pInternal)));
}

Uniquis::DirectX12::VideoDecodeCommandList::~VideoDecodeCommandList()
{
	this->pInternal->Release();
}

void Uniquis::DirectX12::VideoDecodeCommandList::decode()
{

}

ID3D12VideoDecodeCommandList1* Uniquis::DirectX12::VideoDecodeCommandList::operator*() const
{
	return this->pInternal;
}

ID3D12VideoDecodeCommandList1* Uniquis::DirectX12::VideoDecodeCommandList::operator->() const
{
	return this->pInternal;
}