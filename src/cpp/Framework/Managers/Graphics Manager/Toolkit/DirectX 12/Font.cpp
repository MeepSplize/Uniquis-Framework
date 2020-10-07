#include "pch.h"

#include "bin\\Include\\FreeType\\ft2build.h"

#include FT_FREETYPE_H
#include FT_BITMAP_H

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Font.h"

Uniquis::DirectX12::Font::Font(      DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap, 
							   const CommandList&                                           pCommandList, 
							   const Device&                                                pDevice)
{
	std::wstring Filepath;

	Filepath.append(FONT_PATH).append(DEFAULT_FONT);

	FT_Error FreeTypeError;
	
	FT_Matrix Matrix = { static_cast<__int32>((1.0 / 64.0f) * 0x10000L),
                         static_cast<__int32>((0.0)         * 0x10000L),
                         static_cast<__int32>((0.0)         * 0x10000L),
                         static_cast<__int32>((1.0)         * 0x10000L)};

	FT_Library FreeTypeLibrary;

	DEBUG_FREETYPE(FT_Init_FreeType(&(FreeTypeLibrary)));

	FT_Face FontFace;

	DEBUG_FREETYPE(FT_New_Face(FreeTypeLibrary, std::string(Filepath.begin(), Filepath.end()).c_str(), 0, &(FontFace)));

	unsigned __int16 Size = 20;

	unsigned __int16 DPI = 300;
	DEBUG_FREETYPE(FT_Set_Char_Size(FontFace, 0, (64.0f * Size), DPI, DPI));
	//FT_Set_Pixel_Sizes(FontFace, Size, Size);

	this->NewLineSpace = ((FontFace->size->metrics.height / 64.0f) / 1080.0f);

	unsigned __int32 iGlyph = 0;

	FT_Glyph_Metrics RawGlyphMetrics;

	DXGI_FORMAT DXGIFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	unsigned __int16 cCharacters = 100;

	std::vector<unsigned __int8*> vTexturePointers;

	std::vector<std::pair<unsigned __int16, unsigned __int16>> vTextureDimensions;

	vTexturePointers.reserve(cCharacters);
	vTextureDimensions.reserve(cCharacters);

	unsigned __int16 iMetrics;

	FT_Bitmap Bitmap;

	for (unsigned __int16 i = 0; i < cCharacters; i++)
	{
		iGlyph = FT_Get_Char_Index(FontFace, 0x0020 + i);
		
		DEBUG_FREETYPE(FT_Load_Glyph(FontFace, iGlyph, FT_LOAD_DEFAULT));

		DEBUG_FREETYPE(FT_Render_Glyph(FontFace->glyph, FT_RENDER_MODE_LCD));

		RawGlyphMetrics = FontFace->glyph->metrics;
		
		iMetrics = this->vGlyphMetrics.size();

		this->vGlyphMetrics.emplace_back();

		this->vGlyphMetrics[iMetrics].Width             = ((static_cast<float>(RawGlyphMetrics.width)        / 64.0f) / 1080.0f);
		this->vGlyphMetrics[iMetrics].Height            = ((static_cast<float>(RawGlyphMetrics.height)       / 64.0f) / 1080.0f);
		this->vGlyphMetrics[iMetrics].HorizontalBearing = ((static_cast<float>(RawGlyphMetrics.horiBearingX) / 64.0f) / 1080.0f);
		this->vGlyphMetrics[iMetrics].VerticalBearing   = ((static_cast<float>(RawGlyphMetrics.horiBearingY) / 64.0f) / 1080.0f);
		this->vGlyphMetrics[iMetrics].Advance           = ((static_cast<float>(RawGlyphMetrics.horiAdvance)  / 64.0f) / 1080.0f);

		FT_Bitmap_Init(&(Bitmap));
		FT_Bitmap_Copy(FreeTypeLibrary, &FontFace->glyph->bitmap, &Bitmap);
		//DEBUG_FREETYPE(FT_Bitmap_Convert(FreeTypeLibrary, &(FontFace->glyph->bitmap), &(Bitmap), 4));

		if ((Bitmap.pitch * Bitmap.rows) > 0)
		{	
			vTextureDimensions.emplace_back(Bitmap.width, Bitmap.rows);

			// Make Image

			vTexturePointers.emplace_back();

			vTexturePointers[vTexturePointers.size() - 1] = reinterpret_cast<unsigned __int8*>(malloc(4 * (Bitmap.width * Bitmap.rows)));

			unsigned __int8* pTexture = vTexturePointers[vTexturePointers.size() - 1];

			memset(pTexture, 255, (4 * (Bitmap.width * Bitmap.rows)));

			for (unsigned __int16 j = 0; j < Bitmap.rows; j++)
			{
				for (unsigned __int16 k = 3; k < (4 * Bitmap.width); k += 4)
				{
					pTexture[j * (4 * Bitmap.width) + k] = Bitmap.buffer[j * Bitmap.pitch + ((k - 3) / 4)];
				}
			}

			// Debug Text Output

			if (false)
			{
				for (unsigned __int16 j = 0; j < Bitmap.rows; j++)
				{
					for (unsigned __int16 k = 3; k < (4 * Bitmap.width); k += 4)
					{
						if (pTexture[j * (4 * Bitmap.width) + k] == 0)
						OutputDebugStringA(std::string("-").c_str());
						else
						OutputDebugStringA(std::string("O").c_str());
					}

					OutputDebugStringW(L"\n");
				}
			}
		}
		else
		{
			this->viCharactersWithoutBitmap.emplace_back(i);
		}

		FT_Bitmap_Done(FreeTypeLibrary, &(Bitmap));
	}

	TextureAtlasDescription AtlasDescription = {};

	AtlasDescription.HorizontalSpacing  = 10;
	AtlasDescription.VerticalSpacing    = 10;
	AtlasDescription.Width              = 1024;
	AtlasDescription.Height             = 1024;
	AtlasDescription.pTexturePointers   = vTexturePointers.data();
	AtlasDescription.vTextureDimensions = std::move(vTextureDimensions);

	this->pTextureAtlas = std::make_unique<TextureAtlas>(std::move(AtlasDescription), pCommandList, pDevice);

	D3D12_SHADER_RESOURCE_VIEW_DESC ShaderResourceDescriptor = {};

	ShaderResourceDescriptor.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	ShaderResourceDescriptor.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
	ShaderResourceDescriptor.ViewDimension           = D3D12_SRV_DIMENSION_TEXTURE2D;
	ShaderResourceDescriptor.Texture2D.MipLevels     = 1;

	pDevice->CreateShaderResourceView(**(this->pTextureAtlas->pTextureResource), &(ShaderResourceDescriptor), pDescriptorHeap.getCPUHandleToDescriptor(190));

	FT_Done_Face(FontFace);

	FT_Done_FreeType(FreeTypeLibrary);
}

Uniquis::DirectX12::Font::~Font()
{

}