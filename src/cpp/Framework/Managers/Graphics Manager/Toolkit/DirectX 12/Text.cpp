#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Text.h"

Uniquis::DirectX12::Text::Text(      DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
				               const CommandList&                                           pCommandList,
				               const Device&                                                pDevice)
{
	
}

Uniquis::DirectX12::Text::Text(      Uniquis::Text*                                         pText,
							         std::vector<std::unique_ptr<Font>>&                    pvpFonts,
							         ModelHeap&                                             pModelHeap,
	                                 DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
				               const CommandList&                                           pCommandList,
				               const Device&                                                pDevice)
{
	this->bind(pText);

	Font* pFont = pvpFonts[*(this->piFont)].get();

	std::vector<Vertex>           vVertices;
	std::vector<unsigned __int32> vIndices;

	Vector<2> Origin;

	Vector<3> Position;
	Vector<3> Normal;
	Vector<2> vTextureCoordinates;

	Normal.vComponents[2] = 1.0f;

	unsigned __int16 iCharacter;
	unsigned __int16 cSkippedCharacters = 0;
	unsigned __int16 cTempSkippedCharacters = 0;
	unsigned __int32 iIndex;
	unsigned __int16 iTextureCoordinates;

	for (unsigned __int32 i = 0; i < this->pString->length(); i++)
	{
		iCharacter = (this->pString->at(i) - 32);

		if (iCharacter == 65514)
		{
			Origin.vComponents[0]  = 0.0f;
			Origin.vComponents[1] -= pFont->NewLineSpace;

			cSkippedCharacters++;

			goto Continue;
		}
		else if (iCharacter > pFont->vGlyphMetrics.size())
		{
			OutputDebugStringA(std::to_string(i).append("\n").c_str());

			__debugbreak();
		}

		for (unsigned __int16 j = 0; j < pFont->viCharactersWithoutBitmap.size(); j++)
		{
			if      (pFont->viCharactersWithoutBitmap[j] <  iCharacter) (cTempSkippedCharacters++);
			else if (pFont->viCharactersWithoutBitmap[j] == iCharacter)
			{		
				cSkippedCharacters++;

				Origin.vComponents[0] += pFont->vGlyphMetrics[iCharacter].Advance;

				goto Continue;
			}
		}

		iTextureCoordinates = (4 * (iCharacter - cTempSkippedCharacters));

		Position.vComponents[0] = (Origin.vComponents[0] + pFont->vGlyphMetrics[iCharacter].HorizontalBearing);
		Position.vComponents[1] = (Origin.vComponents[1] + pFont->vGlyphMetrics[iCharacter].VerticalBearing);

		vTextureCoordinates = pFont->pTextureAtlas->vTextureCoordinates[iTextureCoordinates];

		vVertices.emplace_back(Position, Normal, vTextureCoordinates);

		Position.vComponents[0] += pFont->vGlyphMetrics[iCharacter].Width;

		vTextureCoordinates = pFont->pTextureAtlas->vTextureCoordinates[iTextureCoordinates + 1];

		vVertices.emplace_back(Position, Normal, vTextureCoordinates);

		Position.vComponents[1] -= pFont->vGlyphMetrics[iCharacter].Height;

		vTextureCoordinates = pFont->pTextureAtlas->vTextureCoordinates[iTextureCoordinates + 2];

		vVertices.emplace_back(Position, Normal, vTextureCoordinates);

		Position.vComponents[0] -= pFont->vGlyphMetrics[iCharacter].Width;

		vTextureCoordinates = pFont->pTextureAtlas->vTextureCoordinates[iTextureCoordinates + 3];

		vVertices.emplace_back(Position, Normal, vTextureCoordinates);

		iIndex = (4 * (i - cSkippedCharacters));

		vIndices.emplace_back(iIndex);
		vIndices.emplace_back(iIndex + 1);
		vIndices.emplace_back(iIndex + 2);

		vIndices.emplace_back(iIndex);
		vIndices.emplace_back(iIndex + 2);
		vIndices.emplace_back(iIndex + 3);

		Origin.vComponents[0] += pFont->vGlyphMetrics[iCharacter].Advance;

		Continue:
		{
			cTempSkippedCharacters = 0;
		}
	}

	pModelHeap.add(1000, std::move(vIndices), std::move(vVertices), pCommandList, pDevice);
}

Uniquis::DirectX12::Text::~Text()
{

}

void Uniquis::DirectX12::Text::bind(Uniquis::Text* pText)
{
	__int8* p = reinterpret_cast<__int8*>(pText);

	this->piFont = reinterpret_cast<unsigned __int16*>(p);

	p += 8; 

	this->pString = reinterpret_cast<std::wstring*>(p);
}

void Uniquis::DirectX12::Text::update()
{
	unsigned __int32 Width = 0;

	for (unsigned __int32 i = 0; i < this->pString->length(); i++)
	{
		wchar_t lol = this->pString[0][i];
	}
}