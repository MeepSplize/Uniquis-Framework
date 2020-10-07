#pragma once

#include "Font.h"
#include "Object.h"
#include "ModelHeap.h"

namespace Uniquis
{
	class Text;

	namespace DirectX12
	{
		class Text
		{
		private:

			std::unique_ptr<Object> pObject;

		public:

			unsigned __int16* piFont;

			std::wstring* pString;

		public:

			Text() = delete;

			Text(      DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
				 const CommandList&                                           pCommandList,
				 const Device&                                                pDevice);

			Text(      Uniquis::Text*                                         pText,
				       std::vector<std::unique_ptr<Font>>&                    pvpFonts,
				       ModelHeap&                                             pModelHeap,
				       DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
				 const CommandList&                                           pCommandList,
				 const Device&                                                pDevice);

			~Text();

		public:

			void bind(Uniquis::Text* pText);

			void update();
		};
	}
}