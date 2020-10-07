#include "pch.h"

#include "bin\\Include\\FreeType\\ft2build.h"
#include FT_FREETYPE_H
#include FT_BITMAP_H

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Texture.h"

Uniquis::DirectX12::Texture::Texture(DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap, const CommandList& pCommandList, const Device& pDevice)
{
	std::shared_ptr<ResourceDescription<ResourceType::Texture2D>> pTextureResourceDescription;

	std::wstring Filepath;

	__int32 ImageBytesPerRow = 0;

	unsigned char* pImageData = nullptr;
	
	Filepath.append(L"").append(L"Text").append(L".png");
	
	__int32 ImageSize = this->load(Filepath, ImageBytesPerRow, &(pImageData), pTextureResourceDescription, pDevice);

	pTextureResourceDescription->pClearValue.reset();
	
	if (ImageSize > 0)
	{
		HRESULT hResult;

		HeapDescription<HeapType::Default> DefaultHeapDescription(1, **(pTextureResourceDescription), HeapFlags::ALLOW_ONLY_NON_RT_DS_TEXTURES, pDevice);

		this->pDefaultHeap = std::make_unique<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);

		this->pTextureResource = std::make_unique<Resource<ResourceType::Texture2D>>(0, *(pTextureResourceDescription), *(this->pDefaultHeap), pDevice);

		unsigned __int64 UploadHeapByteSize;

		pDevice->GetCopyableFootprints(&(pTextureResourceDescription->InternalDescription), 0, 1, 0, nullptr, nullptr, nullptr, &(UploadHeapByteSize));

		ResourceDescription<ResourceType::Buffer> BufferDescription(UploadHeapByteSize, 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::GENERIC_READ, ResourceCreation::PLACED, ResourceFlags::NONE);

		HeapDescription<HeapType::Upload> UploadHeapDescription(1, *(BufferDescription), HeapFlags::ALLOW_ONLY_BUFFERS, pDevice);

		this->pUploadHeap = std::make_unique<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

		this->pBufferResource = std::make_unique<Resource<ResourceType::Buffer>>(0, BufferDescription, *(this->pUploadHeap), pDevice);

		(*(this->pBufferResource))->SetName(L"TEXTURE BUFFER RESOURCE");
	
		D3D12_SUBRESOURCE_DATA SubresourceData = {};
	
		SubresourceData.pData      = pImageData;
		SubresourceData.RowPitch   = ImageBytesPerRow;
		SubresourceData.SlicePitch = ImageSize;

		UpdateSubresources(*(pCommandList), **(this->pTextureResource), **(this->pBufferResource), 0, 0, 1, &(SubresourceData));

		pCommandList.transitionResource(*(this->pTextureResource), ResourceStates::PIXEL_SHADER_RESOURCE);
	
		D3D12_SHADER_RESOURCE_VIEW_DESC ShaderResourceDescriptor = {};
	
		ShaderResourceDescriptor.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		ShaderResourceDescriptor.Format                  = pTextureResourceDescription->InternalDescription.Format;
		ShaderResourceDescriptor.ViewDimension           = D3D12_SRV_DIMENSION_TEXTURE2D;
		ShaderResourceDescriptor.Texture2D.MipLevels     = 1;

		pDevice->CreateShaderResourceView(**(this->pTextureResource), &(ShaderResourceDescriptor), pDescriptorHeap.getCPUHandleToDescriptor(pDescriptorHeap.vPartitionDescriptors[2].Begin + pDescriptorHeap.vPartitionDescriptors[2].Occupied));

		pDescriptorHeap.vPartitionDescriptors[2]++;

		delete pImageData;
	}
	else
	{
		__debugbreak();
	}
}

Uniquis::DirectX12::Texture::Texture(const std::wstring& pFilename, DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap, const CommandList& pCommandList, const Device& pDevice)
{
	std::shared_ptr<ResourceDescription<ResourceType::Texture2D>> pTextureResourceDescription;

	std::wstring Filepath;

	__int32 ImageBytesPerRow = 0;

	unsigned char* pImageData = nullptr;
	
	Filepath.append(L"").append(pFilename);
	
	__int32 ImageSize = this->load(Filepath, ImageBytesPerRow, &(pImageData), pTextureResourceDescription, pDevice);

	pTextureResourceDescription->pClearValue.reset();
	
	if (ImageSize > 0)
	{
		HRESULT hResult;

		HeapDescription<HeapType::Default> DefaultHeapDescription(1, **(pTextureResourceDescription), HeapFlags::ALLOW_ONLY_NON_RT_DS_TEXTURES, pDevice);

		this->pDefaultHeap = std::make_unique<Heap<HeapType::Default>>(DefaultHeapDescription, pDevice);

		this->pTextureResource = std::make_unique<Resource<ResourceType::Texture2D>>(0, *(pTextureResourceDescription), *(this->pDefaultHeap), pDevice);

		(*(this->pTextureResource))->SetName(L"TEXTURE RESOURCE");

		unsigned __int64 UploadHeapByteSize;

		// this function gets the size an upload buffer needs to be to upload a texture to the gpu.
		// each row must be 256 byte aligned except for the last row, which can just be the size in bytes of the row
		// eg. textureUploadBufferSize = ((((width * numBytesPerPixel) + 255) & ~255) * (height - 1)) + (width * numBytesPerPixel);
		//textureUploadBufferSize = (((imageBytesPerRow + 255) & ~255) * (textureDesc.Height - 1)) + imageBytesPerRow;

		pDevice->GetCopyableFootprints(&(pTextureResourceDescription->InternalDescription), 0, 1, 0, nullptr, nullptr, nullptr, &(UploadHeapByteSize));
	


		ResourceDescription<ResourceType::Buffer> BufferDescription(UploadHeapByteSize, 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::GENERIC_READ, ResourceCreation::PLACED, ResourceFlags::NONE);

		HeapDescription<HeapType::Upload> UploadHeapDescription(1, *(BufferDescription), HeapFlags::ALLOW_ONLY_BUFFERS, pDevice);

		this->pUploadHeap = std::make_unique<Heap<HeapType::Upload>>(UploadHeapDescription, pDevice);

		this->pBufferResource = std::make_unique<Resource<ResourceType::Buffer>>(0, BufferDescription, *(this->pUploadHeap), pDevice);

		(*(this->pBufferResource))->SetName(L"TEXTURE BUFFER RESOURCE");

		//hResult = this->pDevice->CreateCommittedResource(
		//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 
		//	D3D12_HEAP_FLAG_NONE,
		//	&CD3DX12_RESOURCE_DESC::Buffer(UploadHeapByteSize), // resource description for a buffer (storing the image data in this heap just to copy to the default heap)
		//	D3D12_RESOURCE_STATE_GENERIC_READ,
		//	nullptr,
		//	IID_PPV_ARGS(&pTextureBufferUploadHeap));
	
		D3D12_SUBRESOURCE_DATA SubresourceData = {};
	
		SubresourceData.pData      = pImageData;
		SubresourceData.RowPitch   = ImageBytesPerRow;
		SubresourceData.SlicePitch = ImageSize;

		UpdateSubresources(*(pCommandList), **(this->pTextureResource), **(this->pBufferResource), 0, 0, 1, &(SubresourceData));

		pCommandList.transitionResource(*(this->pTextureResource), ResourceStates::PIXEL_SHADER_RESOURCE);
	
		D3D12_SHADER_RESOURCE_VIEW_DESC ShaderResourceDescriptor = {};
	
		ShaderResourceDescriptor.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		ShaderResourceDescriptor.Format                  = pTextureResourceDescription->InternalDescription.Format;
		ShaderResourceDescriptor.ViewDimension           = D3D12_SRV_DIMENSION_TEXTURE2D;
		ShaderResourceDescriptor.Texture2D.MipLevels     = 1;

		pDevice->CreateShaderResourceView(**(this->pTextureResource), &(ShaderResourceDescriptor), pDescriptorHeap.getCPUHandleToDescriptor(pDescriptorHeap.vPartitionDescriptors[2].Begin + pDescriptorHeap.vPartitionDescriptors[2].Occupied));

		pDescriptorHeap.vPartitionDescriptors[2]++;

		delete pImageData;
	}
	else
	{
		__debugbreak();
	}
}

Uniquis::DirectX12::Texture::~Texture()
{
	
}

__int32 Uniquis::DirectX12::Texture::load(const          std::wstring&                                 pFilename, 
					                                     __int32&                                       imageBytesPerRow,
					                            unsigned char**                                         pImageData,
					                                     std::shared_ptr<ResourceDescription<ResourceType::Texture2D>>& pResourceDescription, 
					                      const          Device&                                       pDevice)
{
	HRESULT hResult;

	static IWICImagingFactory* pWICFactory;

	IWICBitmapDecoder*     WICDecoder   = nullptr;
	IWICBitmapFrameDecode* WICFrame     = nullptr;
	IWICFormatConverter*   WICConverter = nullptr;
	
	bool bImageConverted = false;

	if (pWICFactory == nullptr)
	{
		CoInitializeEx(0, COINIT_MULTITHREADED | COINIT_SPEED_OVER_MEMORY);

		hResult = CoCreateInstance(CLSID_WICImagingFactory,
			                       0,
			                       CLSCTX_INPROC_SERVER,
			                       IID_PPV_ARGS(&(pWICFactory)));

		if (FAILED(hResult)) return 0;
	}

	hResult = pWICFactory->CreateDecoderFromFilename(pFilename.c_str(),                        // Image we want to load in
		                                             0,                               // This is a vendor ID, we do not prefer a specific one so set to null
		                                             UNDEFINED_GENERIC_READ,          // We want to read from this file
		                                             WICDecodeMetadataCacheOnLoad,    // We will cache the metadata right away, rather than when needed, which might be unknown
		                                             &(WICDecoder));                  // the wic decoder to be created

	if (FAILED(hResult)) return 0;

	hResult = WICDecoder->GetFrame(0, &(WICFrame));
	
	if (FAILED(hResult)) return 0;

	WICPixelFormatGUID PixelFormat;

	hResult = WICFrame->GetPixelFormat(&(PixelFormat));
	
	if (FAILED(hResult)) return 0;

	unsigned __int32 TextureWidth;
	unsigned __int32 TextureHeight;

	hResult = WICFrame->GetSize(&(TextureWidth), &(TextureHeight));
	
	if (FAILED(hResult)) return 0;

	DXGI_FORMAT DXGIFormat = GetDXGIFormat(PixelFormat);

	// CONVERSION (IF NECESSARY)

	if (DXGIFormat == DXGI_FORMAT_UNKNOWN)
	{
		WICPixelFormatGUID ConvertedDXGICompatibleWICFormat = GetConvertedDXGICompatibleWICFormat(PixelFormat);

		if (ConvertedDXGICompatibleWICFormat == GUID_WICPixelFormatDontCare) return 0;

		DXGIFormat = GetDXGIFormat(ConvertedDXGICompatibleWICFormat);

		hResult = pWICFactory->CreateFormatConverter(&(WICConverter));
		
		if (FAILED(hResult)) return 0;

		__int32 bConversionPossible = false;

		hResult = WICConverter->CanConvert(PixelFormat, ConvertedDXGICompatibleWICFormat, &(bConversionPossible));
		
		if (FAILED(hResult) || !(bConversionPossible)) return 0;

		hResult = WICConverter->Initialize(WICFrame, ConvertedDXGICompatibleWICFormat, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
		
		if (FAILED(hResult)) return 0;

		bImageConverted = true;
	}

	unsigned __int32 BitsPerPixel = GetBitsPerPixel(DXGIFormat);

	imageBytesPerRow = (TextureWidth * BitsPerPixel) / 8;

	unsigned __int32 ImageSize = (imageBytesPerRow * TextureHeight);

	*(pImageData) = reinterpret_cast<unsigned char*>(malloc(ImageSize));

	// DEPLOY IMAGE DATA

	WICRect Rectangle;

	Rectangle.X      = 0;
	Rectangle.Y      = 0;
	Rectangle.Width  = TextureWidth;
	Rectangle.Height = TextureHeight;

	if (!(bImageConverted))
	{
		hResult = WICFrame->CopyPixels(0, imageBytesPerRow, ImageSize, *(pImageData));
		
		if (FAILED(hResult)) return 0;
	}
	else
	{
		hResult = WICConverter->CopyPixels(0, imageBytesPerRow, ImageSize, *(pImageData));
		
		if (FAILED(hResult)) return 0;
	}
	
	FT_Error FreeTypeError;
	
	FT_Library FreeTypeLibrary;

	FreeTypeError = FT_Init_FreeType(&(FreeTypeLibrary));

	if (FreeTypeError)
	{
		__debugbreak();
	}

	FT_Face FontFace;

	FreeTypeError = FT_New_Face(FreeTypeLibrary, "res/Fonts/Brandon_bld.otf", 0, &(FontFace));

	if (FreeTypeError)
	{
		__debugbreak();
	}

	FT_Set_Char_Size(FontFace,
          0,       /* char_width in 1/64th of points  */
          16*64,   /* char_height in 1/64th of points */
          1920,     /* horizontal device resolution    */
          1080 );   /* vertical device resolution      */

	unsigned __int32 iGlyph = FT_Get_Char_Index(FontFace, 0x0041);

	FreeTypeError = FT_Load_Glyph(FontFace, iGlyph, FT_LOAD_DEFAULT);

	if (FreeTypeError)
	{
		__debugbreak();
	}

	FreeTypeError = FT_Render_Glyph(FontFace->glyph, FT_RENDER_MODE_LCD);

	if (FreeTypeError)
	{
		__debugbreak();
	}

	//FT_Bitmap Bitmap;

	//FT_Bitmap_Convert(FreeTypeLibrary,
    //                  &(FontFace->glyph->bitmap),
    //                  &(Bitmap),
    //                  4);

	if (FreeTypeError)
	{
		__debugbreak();
	}

	FT_Bitmap Bitmap = FontFace->glyph->bitmap;

	FT_Glyph_Metrics Metrics = FontFace->glyph->metrics;

	TextureWidth = Bitmap.width;
	TextureHeight = Bitmap.rows;

	*(pImageData) = Bitmap.buffer;

	imageBytesPerRow = Bitmap.pitch;

	ImageSize = (imageBytesPerRow * TextureHeight);

	*(pImageData) = reinterpret_cast<unsigned char*>(malloc(ImageSize));

	unsigned __int32 ColumnStart = Metrics.horiBearingX >> 6;
	unsigned __int32 RowStart    = Metrics.horiBearingY >> 6;

	//for (unsigned __int32 iRow = 0; iRow < Bitmap.rows; iRow++)
	//{
	//    unsigned __int32 Row = (RowStart + iRow);
	//
	//    for (unsigned __int32 iColumn = 0; iColumn < Bitmap.width; iColumn++)
	//    {
	//        unsigned __int32 Column = (ColumnStart + iColumn);
	//
	//        (*(pImageData))[Column + Row * Bitmap.pitch]     = Bitmap.buffer[iRow * Bitmap.pitch + iColumn];
	//        (*(pImageData))[Column + Row * Bitmap.pitch + 1] = Bitmap.buffer[iRow * Bitmap.pitch + iColumn + 1];
	//        (*(pImageData))[Column + Row * Bitmap.pitch + 2] = Bitmap.buffer[iRow * Bitmap.pitch + iColumn + 2];
	//		(*(pImageData))[Column + Row * Bitmap.pitch + 3] = 255;
	//	}
	//}

	DXGIFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	//for (unsigned __int32 i = 0; i < ImageSize; i++)
	//{
	//	OutputDebugStringA(std::to_string((signed __int8) pImageData[i]).append(" ").c_str());
	//}

	pResourceDescription = std::make_shared<ResourceDescription<ResourceType::Texture2D>>(TextureWidth, TextureHeight, 1, 1, DXGIFormat, SampleDescription(1, 0), &(ClearValue( { 0.0f, 0.0f, 0.0f, 1.0f } )), ResourceStates::COPY_DESTINATION, ResourceCreation::PLACED, ResourceFlags::NONE);

	return ImageSize;
}

DXGI_FORMAT Uniquis::DirectX12::Texture::GetDXGIFormat(WICPixelFormatGUID& pWicFormatGUID)
{
		 if (pWicFormatGUID == GUID_WICPixelFormat128bppRGBAFloat)	  return DXGI_FORMAT_R32G32B32A32_FLOAT;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppRGBAHalf)	  return DXGI_FORMAT_R16G16B16A16_FLOAT;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppRGBA)		  return DXGI_FORMAT_R16G16B16A16_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppRGBA)		  return DXGI_FORMAT_R8G8B8A8_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppBGRA)		  return DXGI_FORMAT_B8G8R8A8_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppBGR)			  return DXGI_FORMAT_B8G8R8X8_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppRGBA1010102XR) return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppRGBA1010102)	  return DXGI_FORMAT_R10G10B10A2_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat16bppBGRA5551)	  return DXGI_FORMAT_B5G5R5A1_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat16bppBGR565)		  return DXGI_FORMAT_B5G6R5_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppGrayFloat)	  return DXGI_FORMAT_R32_FLOAT;
	else if (pWicFormatGUID == GUID_WICPixelFormat16bppGrayHalf)	  return DXGI_FORMAT_R16_FLOAT;
	else if (pWicFormatGUID == GUID_WICPixelFormat16bppGray)		  return DXGI_FORMAT_R16_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat8bppGray)			  return DXGI_FORMAT_R8_UNORM;
	else if (pWicFormatGUID == GUID_WICPixelFormat8bppAlpha)		  return DXGI_FORMAT_A8_UNORM;

	else return DXGI_FORMAT_UNKNOWN;
}

WICPixelFormatGUID Uniquis::DirectX12::Texture::GetConvertedDXGICompatibleWICFormat(WICPixelFormatGUID& pWicFormatGUID)
{
	     if (pWicFormatGUID == GUID_WICPixelFormatBlackWhite)           return GUID_WICPixelFormat8bppGray;
	else if (pWicFormatGUID == GUID_WICPixelFormat1bppIndexed)          return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat2bppIndexed)          return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat4bppIndexed)          return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat8bppIndexed)          return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat2bppGray)             return GUID_WICPixelFormat8bppGray;
	else if (pWicFormatGUID == GUID_WICPixelFormat4bppGray)             return GUID_WICPixelFormat8bppGray;
	else if (pWicFormatGUID == GUID_WICPixelFormat16bppGrayFixedPoint)  return GUID_WICPixelFormat16bppGrayHalf;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppGrayFixedPoint)  return GUID_WICPixelFormat32bppGrayFloat;
	else if (pWicFormatGUID == GUID_WICPixelFormat16bppBGR555)          return GUID_WICPixelFormat16bppBGRA5551;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppBGR101010)       return GUID_WICPixelFormat32bppRGBA1010102;
	else if (pWicFormatGUID == GUID_WICPixelFormat24bppBGR)             return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat24bppRGB)             return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppPBGRA)           return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppPRGBA)           return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat48bppRGB)             return GUID_WICPixelFormat64bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat48bppBGR)             return GUID_WICPixelFormat64bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppBGRA)            return GUID_WICPixelFormat64bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppPRGBA)           return GUID_WICPixelFormat64bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppPBGRA)           return GUID_WICPixelFormat64bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat48bppRGBFixedPoint)   return GUID_WICPixelFormat64bppRGBAHalf;
	else if (pWicFormatGUID == GUID_WICPixelFormat48bppBGRFixedPoint)   return GUID_WICPixelFormat64bppRGBAHalf;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppRGBAFixedPoint)  return GUID_WICPixelFormat64bppRGBAHalf;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppBGRAFixedPoint)  return GUID_WICPixelFormat64bppRGBAHalf;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppRGBFixedPoint)   return GUID_WICPixelFormat64bppRGBAHalf;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppRGBHalf)         return GUID_WICPixelFormat64bppRGBAHalf;
	else if (pWicFormatGUID == GUID_WICPixelFormat48bppRGBHalf)         return GUID_WICPixelFormat64bppRGBAHalf;
	else if (pWicFormatGUID == GUID_WICPixelFormat128bppPRGBAFloat)     return GUID_WICPixelFormat128bppRGBAFloat;
	else if (pWicFormatGUID == GUID_WICPixelFormat128bppRGBFloat)       return GUID_WICPixelFormat128bppRGBAFloat;
	else if (pWicFormatGUID == GUID_WICPixelFormat128bppRGBAFixedPoint) return GUID_WICPixelFormat128bppRGBAFloat;
	else if (pWicFormatGUID == GUID_WICPixelFormat128bppRGBFixedPoint)  return GUID_WICPixelFormat128bppRGBAFloat;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppRGBE)            return GUID_WICPixelFormat128bppRGBAFloat;
	else if (pWicFormatGUID == GUID_WICPixelFormat32bppCMYK)            return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppCMYK)            return GUID_WICPixelFormat64bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat40bppCMYKAlpha)       return GUID_WICPixelFormat64bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat80bppCMYKAlpha)       return GUID_WICPixelFormat64bppRGBA;

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)

	else if (pWicFormatGUID == GUID_WICPixelFormat32bppRGB)       return GUID_WICPixelFormat32bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppRGB)       return GUID_WICPixelFormat64bppRGBA;
	else if (pWicFormatGUID == GUID_WICPixelFormat64bppPRGBAHalf) return GUID_WICPixelFormat64bppRGBAHalf;

#endif

	else return GUID_WICPixelFormatDontCare;
}

__int32 Uniquis::DirectX12::Texture::GetBitsPerPixel(DXGI_FORMAT& pDXGIFormat)
{
		 if (pDXGIFormat == DXGI_FORMAT_R32G32B32A32_FLOAT)		   return 128;
	else if (pDXGIFormat == DXGI_FORMAT_R16G16B16A16_FLOAT)		   return 64;
	else if (pDXGIFormat == DXGI_FORMAT_R16G16B16A16_UNORM)		   return 64;
	else if (pDXGIFormat == DXGI_FORMAT_R8G8B8A8_UNORM)			   return 32;
	else if (pDXGIFormat == DXGI_FORMAT_B8G8R8A8_UNORM)			   return 32;
	else if (pDXGIFormat == DXGI_FORMAT_B8G8R8X8_UNORM)			   return 32;
	else if (pDXGIFormat == DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM) return 32;
	else if (pDXGIFormat == DXGI_FORMAT_R10G10B10A2_UNORM)		   return 32;
	else if (pDXGIFormat == DXGI_FORMAT_B5G5R5A1_UNORM)			   return 16;
	else if (pDXGIFormat == DXGI_FORMAT_B5G6R5_UNORM)			   return 16;
	else if (pDXGIFormat == DXGI_FORMAT_R32_FLOAT)				   return 32;
	else if (pDXGIFormat == DXGI_FORMAT_R16_FLOAT)				   return 16;
	else if (pDXGIFormat == DXGI_FORMAT_R16_UNORM)				   return 16;
	else if (pDXGIFormat == DXGI_FORMAT_R8_UNORM)				   return 8;
	else if (pDXGIFormat == DXGI_FORMAT_A8_UNORM)				   return 8;
}