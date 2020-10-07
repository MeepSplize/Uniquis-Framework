#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\TextureAtlas.h"

Uniquis::DirectX12::TextureAtlasDescription::TextureAtlasDescription()
{

}

Uniquis::DirectX12::TextureAtlasDescription::~TextureAtlasDescription()
{

}

Uniquis::DirectX12::TextureAtlas::TextureAtlas(const TextureAtlasDescription& pDescription,
					                           const CommandList&             pCommandList,
					                           const Device&                  pDevice)

	: Width(pDescription.Width), Height(pDescription.Height)
{
	unsigned __int32 Pitch = (4 * pDescription.Width);

	// Resources

	ResourceDescription<ResourceType::Texture2D> TextureResourceDescription(pDescription.Width, pDescription.Height, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, SampleDescription(1, 0), &(ClearValue({ 0.0f, 0.0f, 0.0f, 1.0f })), ResourceStates::COPY_DESTINATION, ResourceCreation::PLACED, ResourceFlags::NONE);

	TextureResourceDescription.pClearValue.reset();

	// -> Size Calculation

	unsigned __int64 DataByteSize  = (Pitch * pDescription.Height);
	unsigned __int64 AlignmentRest = (DataByteSize % 65536);

	unsigned __int64 TextureHeapByteSize = (AlignmentRest ? (DataByteSize + (65536 - AlignmentRest)) : DataByteSize);

	unsigned __int64 BufferHeapByteSize;

	pDevice->GetCopyableFootprints(&(TextureResourceDescription.InternalDescription), 0, 1, 0, nullptr, nullptr, nullptr, &(BufferHeapByteSize));

	// -> Initialization

	// -> -> Heaps

	HeapDescription<HeapType::Default> TextureHeapDescription(65536, TextureHeapByteSize, HeapFlags::ALLOW_ONLY_NON_RT_DS_TEXTURES);

	this->pTextureHeap = std::make_unique<Heap<HeapType::Default>>(TextureHeapDescription, pDevice);

	HeapDescription<HeapType::Upload> BufferHeapDescription(65536, BufferHeapByteSize, HeapFlags::ALLOW_ONLY_BUFFERS);

	this->pBufferHeap = std::make_unique<Heap<HeapType::Upload>>(BufferHeapDescription, pDevice);

	// -> -> Resources

	this->pTextureResource = std::make_unique<Resource<ResourceType::Texture2D>>(0, TextureResourceDescription, *(this->pTextureHeap), pDevice);

	ResourceDescription<ResourceType::Buffer> BufferResourceDescription(BufferHeapByteSize, 1, 1, 1, DXGI_FORMAT_UNKNOWN, SampleDescription(1, 0), nullptr, ResourceStates::GENERIC_READ, ResourceCreation::PLACED, ResourceFlags::NONE);

	this->pBufferResource = std::make_unique<Resource<ResourceType::Buffer>>(0, BufferResourceDescription, *(this->pBufferHeap), pDevice);

	// Packing

	unsigned __int8* pBuffer = reinterpret_cast<unsigned __int8*>(malloc(4 * (pDescription.Width * pDescription.Height)));

	DEBUG_ONLY
	(
		memset(pBuffer, 0, (4 * pDescription.Width * pDescription.Height));
	);

	unsigned __int32 TexturePitch;
	unsigned __int16 TextureWidth;
	unsigned __int16 TextureHeight;

	unsigned __int32 CurrentRow     = 0;
	unsigned __int32 CurrentCollumn = 0;

	unsigned __int32 VerticalOffset = 0;

	unsigned __int8* pTexture;

	float TextureCoordinates[2];

	for (unsigned __int16 i = 0; i < pDescription.vTextureDimensions.size(); i++)
	{
		pTexture = pDescription.pTexturePointers[i];

		TexturePitch  = (4 * pDescription.vTextureDimensions[i].first);
		TextureWidth  = pDescription.vTextureDimensions[i].first;
		TextureHeight = pDescription.vTextureDimensions[i].second;

		if (TextureHeight <= (pDescription.Height - CurrentRow))
		{
			if ((0 < static_cast<__int32>(Pitch - CurrentCollumn)) && (TexturePitch <= (Pitch - CurrentCollumn)))
			{
				TextureCoordinates[0] = ((CurrentCollumn / 4) / static_cast<float>(pDescription.Width));
				TextureCoordinates[1] = (CurrentRow / static_cast<float>(pDescription.Height));

				this->vTextureCoordinates.emplace_back(TextureCoordinates);

				TextureCoordinates[0] += ((TexturePitch / 4) / static_cast<float>(pDescription.Width));

				this->vTextureCoordinates.emplace_back(TextureCoordinates);
				
				TextureCoordinates[1] += (TextureHeight / static_cast<float>(pDescription.Height));

				this->vTextureCoordinates.emplace_back(TextureCoordinates);

				TextureCoordinates[0] = ((CurrentCollumn / 4) / static_cast<float>(pDescription.Width));

				this->vTextureCoordinates.emplace_back(TextureCoordinates);

				// Pack Texture

				for (unsigned __int32 j = 0; j < TextureHeight; j++)
				{
					for (unsigned __int32 k = 0; k < TexturePitch; k++)
					{
						pBuffer[(Pitch * CurrentRow) + (Pitch * j) + CurrentCollumn + k] = pTexture[j * TexturePitch + k];
					}
				}

				CurrentCollumn += (TexturePitch + (4 * pDescription.HorizontalSpacing));

				if (TextureHeight > VerticalOffset) (VerticalOffset = TextureHeight);
			}
			else
			{
				CurrentRow     += (VerticalOffset + pDescription.VerticalSpacing);
				CurrentCollumn  = 0;

				VerticalOffset = 0;

				if (TextureHeight <= (pDescription.Height - CurrentRow))
				{
					TextureCoordinates[0] = ((CurrentCollumn / 4) / static_cast<float>(pDescription.Width));
					TextureCoordinates[1] = (CurrentRow / static_cast<float>(pDescription.Height));

					this->vTextureCoordinates.emplace_back(TextureCoordinates);

					TextureCoordinates[0] += ((TexturePitch / 4) / static_cast<float>(pDescription.Width));

					this->vTextureCoordinates.emplace_back(TextureCoordinates);
					
					TextureCoordinates[1] += (TextureHeight / static_cast<float>(pDescription.Height));

					this->vTextureCoordinates.emplace_back(TextureCoordinates);

					TextureCoordinates[0] = ((CurrentCollumn / 4) / static_cast<float>(pDescription.Width));

					this->vTextureCoordinates.emplace_back(TextureCoordinates);

					// Pack Texture

					for (unsigned __int32 j = 0; j < TextureHeight; j++)
					{
						for (unsigned __int32 k = 0; k < TexturePitch; k++)
						{
							pBuffer[(Pitch * CurrentRow) + (Pitch * j) + CurrentCollumn + k] = pTexture[j * TexturePitch + k];
						}
					}

					CurrentCollumn += (TexturePitch + (4 * pDescription.HorizontalSpacing));

					if (TextureHeight > VerticalOffset) (VerticalOffset = TextureHeight);
				}
				else
				{
					__debugbreak();    /* The Textures don't fit into the Atlas width the specified Dimension */
				}
			}
		}
		else
		{
			__debugbreak();    /* The Textures don't fit into the Atlas width the specified Dimension */
		}
	}

	D3D12_SUBRESOURCE_DATA SubresourceData = {};

	SubresourceData.pData      = pBuffer;
	SubresourceData.RowPitch   = (4 * pDescription.Width);
	SubresourceData.SlicePitch = (4 * pDescription.Width * pDescription.Height);

	UpdateSubresources(*(pCommandList), **(this->pTextureResource), **(this->pBufferResource), 0, 0, 1, &(SubresourceData));

	pCommandList.transitionResource(*(this->pTextureResource), ResourceStates::PIXEL_SHADER_RESOURCE);

	OutputDebugString(L"[INFO] Texture Packing Done! \n");

	free(pBuffer);
}

Uniquis::DirectX12::TextureAtlas::~TextureAtlas()
{
	
}