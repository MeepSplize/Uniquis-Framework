#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Heap.h"

template<Uniquis::DirectX12::HeapType Type>
Uniquis::DirectX12::Heap<Type>::Heap(HeapDescription<Type>& pDescription, const Device& pDevice)
{
	
}

template<>
Uniquis::DirectX12::Heap<Uniquis::DirectX12::HeapType::Default>::Heap(HeapDescription<Uniquis::DirectX12::HeapType::Default>& pDescription, const Device& pDevice)

	: ByteCapacity(0, 0)
{
	HRESULT hResult;

	pDescription.InternalDescription.Properties.Type = D3D12_HEAP_TYPE_DEFAULT;

	hResult = pDevice->CreateHeap(*(pDescription), IID_PPV_ARGS(&(this->pHeap)));

	if (FAILED(hResult))
	{
		std::string Error = std::system_category().message(hResult);
		
		OutputDebugString(L"[ERROR] Failed to create Default Heap \n");
		OutputDebugStringA(Error.append("\n").c_str());
	}
}

template<>
Uniquis::DirectX12::Heap<Uniquis::DirectX12::HeapType::Upload>::Heap(HeapDescription<Uniquis::DirectX12::HeapType::Upload>& pDescription, const Device& pDevice)

	: ByteCapacity(0, 0)
{
	HRESULT hResult;

	pDescription.InternalDescription.Properties.Type = D3D12_HEAP_TYPE_UPLOAD;

	if (FAILED(pDevice->CreateHeap(*(pDescription), IID_PPV_ARGS(&(this->pHeap)))))
	{
		std::string Error = std::system_category().message(hResult);

		OutputDebugString(L"[ERROR] Failed to create Upload Heap \n");
		OutputDebugStringA(Error.append("\n").c_str());
	}
}

template<Uniquis::DirectX12::HeapType Type>
Uniquis::DirectX12::Heap<Type>::~Heap()
{
	this->pHeap->Release();
}

template<Uniquis::DirectX12::HeapType Type>
ID3D12Heap* Uniquis::DirectX12::Heap<Type>::operator*() const noexcept
{
	return this->pHeap;
}

template<Uniquis::DirectX12::HeapType Type>
ID3D12Heap* Uniquis::DirectX12::Heap<Type>::operator->() const noexcept
{
	return this->pHeap;
}

template class Uniquis::DirectX12::Heap<Uniquis::DirectX12::HeapType::Default>;
template class Uniquis::DirectX12::Heap<Uniquis::DirectX12::HeapType::Upload>;


