#pragma once

#include "Framework\\Managers\\Device Manager\\Core\\DeviceManager.h"

#include "..\\Toolkit\\Window.h"
#include "..\\Toolkit\\WindowClass.h"

namespace Uniquis
{
	class WindowManager
	{
	public:

		std::vector<Window> vWindows;

		std::vector<WindowClass> vWindowClasses;

	private:

		WindowManager();

	public:

		WindowManager(const WindowManager&) = delete;

		WindowManager(const WindowManager&&) = delete;

		~WindowManager();

	public:

		static WindowManager& getReference();

		const UINT8 addWindow(const          wchar_t* name,
							        unsigned __int16  x,
							        unsigned __int16  y,
							        unsigned __int16  width,
							        unsigned __int16  height,
							  const          wchar_t* windowClassName,
							 	    unsigned long     style);

		void addWindowClass(const wchar_t* name);

		void addWindowClass(const wchar_t* name,
							const __int32  icon);

	public:

		void operator=(const WindowManager&) = delete;
	};
}