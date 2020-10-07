#include "pch.h"

#include "Project\\Resources\\Resources.h"

#include "Framework\\Managers\\Window Manager\\Toolkit\\Window.h"

#include "Framework\\Managers\\Window Manager\\Toolkit\\WindowClass.h"

Uniquis::WindowClass::WindowClass(const wchar_t* name) noexcept

	: Name(name) 
{
	HINSTANCE hInstance = GetModuleHandleW(0);

	WNDCLASSEX WindowClassEx = {};

	WindowClassEx.cbSize        = sizeof(WindowClassEx);
	WindowClassEx.style         = CS_OWNDC;
	WindowClassEx.lpfnWndProc   = this->handleMessageSetup;
	WindowClassEx.cbClsExtra    = 0;
	WindowClassEx.cbWndExtra    = 0;
	WindowClassEx.hInstance     = hInstance;
	WindowClassEx.hIcon         = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(APPLICATIONICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));
	WindowClassEx.hCursor       = nullptr;
	WindowClassEx.hbrBackground = nullptr;
	WindowClassEx.lpszMenuName  = nullptr;
	WindowClassEx.lpszClassName = name;
	WindowClassEx.hIconSm       = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(APPLICATIONICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));

	RegisterClassEx(&(WindowClassEx));
}

Uniquis::WindowClass::WindowClass(const wchar_t* name, const int icon) noexcept

	: Name(name) 
{
	HINSTANCE hInstance = GetModuleHandleW(0);

	WNDCLASSEX WindowClassEx = {};

	WindowClassEx.cbSize        = sizeof(WindowClassEx);
	WindowClassEx.style         = CS_OWNDC;
	WindowClassEx.lpfnWndProc   = this->handleMessageSetup;
	WindowClassEx.cbClsExtra    = 0;
	WindowClassEx.cbWndExtra    = 0;
	WindowClassEx.hInstance     = hInstance;
	WindowClassEx.hIcon         = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(icon), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));
	WindowClassEx.hCursor       = nullptr;
	WindowClassEx.hbrBackground = nullptr;
	WindowClassEx.lpszMenuName  = nullptr;
	WindowClassEx.lpszClassName = name;
	WindowClassEx.hIconSm       = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(icon), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));

	RegisterClassEx(&(WindowClassEx));
}

Uniquis::WindowClass::WindowClass(WindowClass&& other)

	: Name(other.Name)
{

}

Uniquis::WindowClass::~WindowClass() 
{
	UnregisterClassW(this->Name, GetModuleHandleW(0));
}

LRESULT CALLBACK Uniquis::WindowClass::handleMessageSetup(HWND hWindow, UINT message, WPARAM wParameter, LPARAM lParameter) noexcept 
{
	if (message == WM_NCCREATE) 
	{
		const CREATESTRUCTW* const pCreateStruct = reinterpret_cast<CREATESTRUCTW*>(lParameter);    // Extract Pointer to Window Class from the Window's Creation Data (CreateStruct)

		Window* const pWindow = static_cast<Window*>(pCreateStruct->lpCreateParams);

		SetWindowLongPtrW(hWindow, GWLP_USERDATA, reinterpret_cast<long long>(pWindow));    // Set WinAPI-managed User Data to store the Pointer to the Window Instance

		SetWindowLongPtrW(hWindow, GWLP_WNDPROC, reinterpret_cast<long long>(&(Window::handleMessageThunk)));    // Set Message Procedure to normal (non-Setup) Handler now that Setup is finished
		
		return pWindow->handleMessageThunk(hWindow, message, wParameter, lParameter);    // Forward Message to the Window's Custom Handler
	}

	return DefWindowProcW(hWindow, message, wParameter, lParameter);    // If WM_NCCREATE Message hasn't arrived yet, handle with Default Handler
}