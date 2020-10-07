#pragma once

namespace Uniquis
{
	class WindowClass
	{
	public:

		const wchar_t* Name;

	public:

		WindowClass(const wchar_t* name) noexcept;

		WindowClass(const wchar_t* name, const int icon) noexcept;

		WindowClass(const WindowClass&) = delete;

		WindowClass(WindowClass&& other);

	public:

		~WindowClass() noexcept;

	private:

		static LRESULT CALLBACK handleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	public:

		void operator=(const WindowClass&) = delete;
	};
}