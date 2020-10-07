#pragma once

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\CommandList.h"
#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\DescriptorHeap.h"
#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Heap.h"
#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Resource.h"

namespace Uniquis::DirectX12
{
	class Texture
	{
	private:

		std::unique_ptr<Resource<ResourceType::Texture2D>> pTextureResource;
		std::unique_ptr<Resource<ResourceType::Buffer>>    pBufferResource;

		std::unique_ptr<Heap<HeapType::Upload>>  pUploadHeap;
		std::unique_ptr<Heap<HeapType::Default>> pDefaultHeap;

	public:

		Texture(DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap, const CommandList& pCommandList, const Device& pDevice);

		Texture(const std::wstring& pFilename, DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap, const CommandList& pCommandList, const Device& pDevice);

		~Texture();

	public:

		static DXGI_FORMAT        GetDXGIFormat(WICPixelFormatGUID& pWicFormatGUID);
		static WICPixelFormatGUID GetConvertedDXGICompatibleWICFormat(WICPixelFormatGUID& pWicFormatGUID);
		static __int32            GetBitsPerPixel(DXGI_FORMAT& pDXGIFormat);

		__int32 load(const          std::wstring&                                 pFilename, 
					                __int32&                                       imageBytesPerRow,
					       unsigned char**                                         pImageData,
					                std::shared_ptr<ResourceDescription<ResourceType::Texture2D>>& pResourceDescription, 
					 const          Device&                                       pDevice);
	};
}