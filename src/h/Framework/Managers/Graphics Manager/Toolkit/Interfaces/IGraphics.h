#pragma once

namespace Uniquis
{
	class Font;
	class Text;
	class Object;

	class IGraphics
	{
	public:

		IGraphics();

	public:

		virtual ~IGraphics() = 0;

	public:

		virtual void bind(Font*   pFont) = 0;
		virtual void bind(Text*   pText) = 0;
		virtual void bind(Object* pObject) = 0;

		virtual void addWindow(const unsigned __int16 width, const unsigned __int16 height, HWND hWindow) = 0;

		virtual void render(const float time, const unsigned __int8 windowIndex) = 0;

		virtual void release()  = 0;
	};
}