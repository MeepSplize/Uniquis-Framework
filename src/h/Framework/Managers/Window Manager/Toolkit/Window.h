#pragma once

#include "Framework\\Managers\\Device Manager\\Core\\DeviceManager.h"

#include "Framework\\Managers\\Graphics Manager\\Core\\GraphicsManager.h"

namespace Uniquis
{
	class WindowDescription
	{
		// ...
	};

	class Window
	{
	private:

		friend class WindowClass;

		friend class WindowManager;

	private:

		std::vector<char> RawBuffer;

		std::vector<HANDLE> AcceptedDeviceHandles;

	public:

		HWND hWindow;

		const wchar_t* Name = L"";

		unsigned __int16 Width;
		unsigned __int16 Height;

	public:

		Window(const wchar_t*		  name,
					 unsigned __int16 x,
					 unsigned __int16 y,
					 unsigned __int16 width,
					 unsigned __int16 height,
			   const wchar_t*         windowClassName,
					 unsigned long	  style);

		Window(const Window&) = delete;

		Window(Window&& other) noexcept;

		~Window();

	private:

		LRESULT handleMessage(HWND hWindow, UINT message, WPARAM wParameter, LPARAM lParameter) noexcept;

		static LRESULT __stdcall handleMessageThunk(HWND hWindow, UINT message, WPARAM wParameter, LPARAM lParameter) noexcept;

	public:

		void setTitle(const std::wstring& title) noexcept;

		void addDevice(const HANDLE hDevice) noexcept;

		const std::optional<int> processMessages();

	public:

		void operator=(const Window&) = delete;
	};
}