#pragma once

#include "..\\..\\Core\\GraphicsManager.h"

namespace Uniquis
{
	class Font
	{
	public:

		std::wstring Name;

	public:

		Font();

		~Font();

	public:

		void bind(GraphicsManager& pGraphicsManager);

	public:

		void operator=(const Font&) = delete;
	};
}