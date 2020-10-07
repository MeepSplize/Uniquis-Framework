#pragma once

#include "Project\\Macros\\Macros.h"

#include "Object.h"
#include "TextureAtlas.h"
#include "CommandList.h"
#include "DescriptorHeap.h"
#include "Heap.h"
#include "Resource.h"

namespace Uniquis
{
	class Font;

	namespace DirectX12
	{
		class GlyphMetrics
		{
		public:

			float Width;
			float Height;
			float HorizontalBearing;
			float VerticalBearing;
			float Advance;

		public:

			GlyphMetrics() = default;

			~GlyphMetrics() = default;
		};

		class Font
		{
		public:

			std::wstring* pName;

			float NewLineSpace;

			std::unique_ptr<TextureAtlas> pTextureAtlas;

			std::vector<GlyphMetrics> vGlyphMetrics;

			std::vector<unsigned __int16> viCharactersWithoutBitmap;

		public:

			Font(      DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
				 const CommandList&                                           pCommandList,
				 const Device&                                                pDevice);

			Font(      Uniquis::Font*                                         pFont,
					   DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
				 const CommandList&                                           pCommandList,
				 const Device&                                                pDevice);

			~Font();

		public:

			void operator=(const Font&) = delete;
		};
	}
}