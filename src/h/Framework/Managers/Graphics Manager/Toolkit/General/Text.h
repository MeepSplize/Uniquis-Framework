#pragma once

#include "..\\..\\Core\\GraphicsManager.h"

namespace Uniquis
{
	class Text
	{
	private:

		unsigned __int16 iFont;

		std::wstring String;

	public:

		Text();

		Text(const std::wstring& pString);

		Text(const unsigned __int16 iFont, const std::wstring& pString);

		~Text();

	public:

		void bind(GraphicsManager& pGraphicsManager);

		void set(const std::wstring& pString);
	};
}