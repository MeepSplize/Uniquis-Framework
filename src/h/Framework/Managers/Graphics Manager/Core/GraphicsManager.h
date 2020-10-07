#pragma once

#include "Framework\\Managers\\Device Manager\\Core\\DeviceManager.h"

#include "..\\Toolkit\\DirectX 12\\DirectX12.h"

#include "..\\Toolkit\\Interfaces\\IGraphics.h"

#include "..\\Toolkit\\General\\Transformation.h"

namespace Uniquis
{
	class Font;
	class Text;
	class Object;

	class GraphicsManager
	{
	public:

		std::unique_ptr<IGraphics> pGraphicsAPI;

	private:

		GraphicsManager();

	public:

		GraphicsManager(const GraphicsManager&) = delete;

		~GraphicsManager();

	public:

		static GraphicsManager& getReference();

		void addWindow(const unsigned __int16 width, const unsigned __int16 height, HWND hWindow);

		void bind(Font*   pFont);
		void bind(Text*   pText);
		void bind(Object* pObject);

		void render(const float time, const unsigned __int8 windowIndex) const;

		void release();

	public:

		void operator=(const GraphicsManager&) = delete;
	};
}