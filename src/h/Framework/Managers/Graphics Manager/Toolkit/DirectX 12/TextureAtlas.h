#pragma once

#include "bin\\Include\\FreeType\\ft2build.h"

#include FT_FREETYPE_H
#include FT_BITMAP_H

#include "Project\\Macros\\Macros.h"

#include "Toolkit\\Math\\Vector.h"

#include "CommandList.h"
#include "DescriptorHeap.h"
#include "Heap.h"
#include "Resource.h"

namespace Uniquis::DirectX12
{
	class TextureAtlasDescription
	{
	public:

		unsigned __int16 HorizontalSpacing;
		unsigned __int16 VerticalSpacing;

		unsigned __int32 Width;
		unsigned __int32 Height;

		unsigned __int8** pTexturePointers;

		std::vector<std::pair<unsigned __int16, unsigned __int16>> vTextureDimensions;

	public:

		TextureAtlasDescription();

		~TextureAtlasDescription();

	public:

		void operator=(const TextureAtlasDescription&) = delete;
	};

	class TextureAtlas
	{
	public:

		std::unique_ptr<Heap<HeapType::Upload>>  pBufferHeap;
		std::unique_ptr<Heap<HeapType::Default>> pTextureHeap;

		std::unique_ptr<Resource<ResourceType::Texture2D>> pTextureResource;
		std::unique_ptr<Resource<ResourceType::Buffer>>    pBufferResource;

	public:

		unsigned __int32 Width;
		unsigned __int32 Height;

		std::vector<Vector<2>> vTextureCoordinates;

	public:

		TextureAtlas() = delete;

		TextureAtlas(const TextureAtlasDescription& pDescription,
					 const CommandList&             pCommandList,
					 const Device&                  pDevice);

		~TextureAtlas();

	public:

		void operator=(const TextureAtlas&) = delete;
	};
}