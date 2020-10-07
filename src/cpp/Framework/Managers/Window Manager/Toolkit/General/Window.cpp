#include "pch.h"

#include "Project\\Resources\\Resources.h"

#include "Framework\\Managers\\Window Manager\\Toolkit\\Window.h"

Uniquis::Window::Window(Window&& other) noexcept

	:				   Name(std::move(other.Name)),
	  AcceptedDeviceHandles(std::move(other.AcceptedDeviceHandles)),
				  RawBuffer(std::move(other.RawBuffer)),
				    hWindow(std::move(other.hWindow)),
				      Width(std::move(other.Width)),
				     Height(std::move(other.Height)) 
{

}

Uniquis::Window::Window(const wchar_t*         name,
					         unsigned __int16 x,
					         unsigned __int16 y,
					         unsigned __int16 width,
					         unsigned __int16 height,
					   const wchar_t*         windowClassName,
					         unsigned long    style)

	:          Width(width), 
	          Height(height)
{
	/* Calculate window size based on desired Client Area Size */

	RECT WindowRectangle = {};

	WindowRectangle.left   = 0;
	WindowRectangle.right  = width  + WindowRectangle.left;
	WindowRectangle.top    = 0;
	WindowRectangle.bottom = height + WindowRectangle.top;

	AdjustWindowRect(&(WindowRectangle), style, false);

	this->hWindow = CreateWindowExW(0,
								    windowClassName,
								    name,
								    style,
								    x, y,
								    (WindowRectangle.right - WindowRectangle.left), (WindowRectangle.bottom - WindowRectangle.top),
								    nullptr,
								    nullptr,
								    GetModuleHandleW(NULL),
								    this);

	if (style == 0)
	{
		SetWindowLongW(this->hWindow, GWL_STYLE, 0);    // Removes all styles
	}

	ShowWindow(this->hWindow, SW_SHOW);

	GraphicsManager::getReference().addWindow(width, height, this->hWindow);
}

Uniquis::Window::~Window()
{
	DestroyWindow(this->hWindow);
}

void Uniquis::Window::setTitle(const std::wstring& title) noexcept
{
	SetWindowText(this->hWindow, title.c_str());

	this->Name = title.c_str();
}

void Uniquis::Window::addDevice(const HANDLE hDevice) noexcept
{
	this->AcceptedDeviceHandles.emplace_back(hDevice);
}

const std::optional<int> Uniquis::Window::processMessages()
{
	MSG Message;

	memset(&(Message), 0, sizeof(MSG));	

	while (PeekMessageW(&(Message), nullptr, 0, 0, PM_REMOVE))
	{
		if (Message.message == WM_QUIT)
		{
			return Message.wParam;
		}

		DispatchMessageW(&(Message));
	}

	return {};
}

LRESULT Uniquis::Window::handleMessage(HWND hWindow, UINT message, WPARAM wParameter, LPARAM lParameter) noexcept
{
	switch (message) 
	{
		case WM_CLOSE: 
		{
			PostQuitMessage(0);
			
			return 0;
		}

		case WM_INPUT:
		{
			unsigned __int32 DataSize;

			GetRawInputData(reinterpret_cast<HRAWINPUT>(lParameter), RID_INPUT, NULL, &(DataSize), sizeof(RAWINPUTHEADER));

			LPBYTE pData = new BYTE[DataSize];

			if (pData == NULL)
			{
				OutputDebugString(L"[ERROR] WM_INPUT size = 0 \n");
			}

			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParameter), RID_INPUT, pData, &(DataSize), sizeof(RAWINPUTHEADER)) != DataSize)
			{
				OutputDebugString(L"[ERROR] GetRawInputData does not return correct size! \n");
			}

			RAWINPUT* pRawInput = reinterpret_cast<RAWINPUT*>(pData);

			DeviceManager& pDeviceManager = DeviceManager::getReference();

			switch (pRawInput->header.dwType)
			{
				case RIM_TYPEMOUSE:
				{
					if (pRawInput->data.mouse.usFlags == MOUSE_MOVE_RELATIVE)
					{
						pDeviceManager.Mouse.x = pRawInput->data.mouse.lLastX;
						pDeviceManager.Mouse.y = pRawInput->data.mouse.lLastY;
					}
					
					if (pRawInput->data.mouse.usButtonFlags & RI_MOUSE_BUTTON_1_DOWN)
					{
						OutputDebugString(L"Left Mouse Button pressed! \n");

						MessageBeep(MB_OK);
					}

					break;
				}

				case RIM_TYPEKEYBOARD:
				{
					switch (pRawInput->data.keyboard.Flags)
					{
						case RI_KEY_MAKE:
						{
							switch (pRawInput->data.keyboard.VKey)
							{
								case 0x30:
								{
									pDeviceManager.Keyboard.bKeys[KEY_0] = true;

									break;
								}

								case 0x31:
								{
									pDeviceManager.Keyboard.bKeys[KEY_1] = true;

									break;
								}

								case 0x32:
								{
									pDeviceManager.Keyboard.bKeys[KEY_2] = true;

									break;
								}

								case 0x33:
								{
									pDeviceManager.Keyboard.bKeys[KEY_3] = true;

									break;
								}

								case 0x34:
								{
									pDeviceManager.Keyboard.bKeys[KEY_4] = true;

									break;
								}

								case 0x35:
								{
									pDeviceManager.Keyboard.bKeys[KEY_5] = true;

									break;
								}

								case 0x36:
								{
									pDeviceManager.Keyboard.bKeys[KEY_6] = true;

									break;
								}

								case 0x37:
								{
									pDeviceManager.Keyboard.bKeys[KEY_7] = true;

									break;
								}

								case 0x38:
								{
									pDeviceManager.Keyboard.bKeys[KEY_8] = true;

									break;
								}

								case 0x39:
								{
									pDeviceManager.Keyboard.bKeys[KEY_9] = true;

									break;
								}

								case 0x41:
								{
									pDeviceManager.Keyboard.bKeys[KEY_A] = true;

									break;
								}

								case 0x42:
								{
									pDeviceManager.Keyboard.bKeys[KEY_B] = true;

									break;
								}

								case 0x43:
								{
									pDeviceManager.Keyboard.bKeys[KEY_C] = true;

									break;
								}

								case 0x44:
								{
									pDeviceManager.Keyboard.bKeys[KEY_D] = true;

									break;
								}

								case 0x45:
								{
									pDeviceManager.Keyboard.bKeys[KEY_E] = true;

									break;
								}

								case 0x46:
								{
									pDeviceManager.Keyboard.bKeys[KEY_F] = true;

									break;
								}

								case 0x47:
								{
									pDeviceManager.Keyboard.bKeys[KEY_G] = true;

									break;
								}

								case 0x48:
								{
									pDeviceManager.Keyboard.bKeys[KEY_H] = true;

									break;
								}

								case 0x49:
								{
									pDeviceManager.Keyboard.bKeys[KEY_I] = true;

									break;
								}

								case 0x4A:
								{
									pDeviceManager.Keyboard.bKeys[KEY_J] = true;

									break;
								}

								case 0x4B:
								{
									pDeviceManager.Keyboard.bKeys[KEY_K] = true;

									break;
								}

								case 0x4C:
								{
									pDeviceManager.Keyboard.bKeys[KEY_L] = true;

									break;
								}

								case 0x4D:
								{
									pDeviceManager.Keyboard.bKeys[KEY_M] = true;

									break;
								}

								case 0x4E:
								{
									pDeviceManager.Keyboard.bKeys[KEY_N] = true;

									break;
								}

								case 0x4F:
								{
									pDeviceManager.Keyboard.bKeys[KEY_O] = true;

									break;
								}

								case 0x50:
								{
									pDeviceManager.Keyboard.bKeys[KEY_P] = true;

									break;
								}

								case 0x51:
								{
									pDeviceManager.Keyboard.bKeys[KEY_Q] = true;

									break;
								}

								case 0x52:
								{
									pDeviceManager.Keyboard.bKeys[KEY_R] = true;

									break;
								}

								case 0x53:
								{
									pDeviceManager.Keyboard.bKeys[KEY_S] = true;

									break;
								}

								case 0x54:
								{
									pDeviceManager.Keyboard.bKeys[KEY_T] = true;

									break;
								}

								case 0x55:
								{
									pDeviceManager.Keyboard.bKeys[KEY_U] = true;

									break;
								}

								case 0x56:
								{
									pDeviceManager.Keyboard.bKeys[KEY_V] = true;

									break;
								}

								case 0x57:
								{
									pDeviceManager.Keyboard.bKeys[KEY_W] = true;

									break;
								}

								case 0x58:
								{
									pDeviceManager.Keyboard.bKeys[KEY_X] = true;

									break;
								}

								case 0x59:
								{
									pDeviceManager.Keyboard.bKeys[KEY_Y] = true;

									break;
								}

								case 0x5A:
								{
									pDeviceManager.Keyboard.bKeys[KEY_Z] = true;

									break;
								}

								case 0x26:
								{
									pDeviceManager.Keyboard.bKeys[KEY_ARROW_UP] = true;

									break;
								}

								case 0x28:
								{
									pDeviceManager.Keyboard.bKeys[KEY_ARROW_DOWN] = true;

									break;
								}

								case 0x25:
								{
									pDeviceManager.Keyboard.bKeys[KEY_ARROW_LEFT] = true;

									break;
								}

								case 0x27:
								{
									pDeviceManager.Keyboard.bKeys[KEY_ARROW_RIGHT] = true;

									break;
								}

								case 0x20:
								{
									pDeviceManager.Keyboard.bKeys[KEY_SPACE] = true;

									break;
								}

								case 0x11:
								{
									pDeviceManager.Keyboard.bKeys[KEY_CTRL] = true;

									break;
								}
							}

							break;
						}

						case RI_KEY_BREAK:
						{
							switch (pRawInput->data.keyboard.VKey)
							{
								case 0x30:
								{
									pDeviceManager.Keyboard.bKeys[KEY_0] = false;

									break;
								}

								case 0x31:
								{
									pDeviceManager.Keyboard.bKeys[KEY_1] = false;

									break;
								}

								case 0x32:
								{
									pDeviceManager.Keyboard.bKeys[KEY_2] = false;

									break;
								}

								case 0x33:
								{
									pDeviceManager.Keyboard.bKeys[KEY_3] = false;

									break;
								}

								case 0x34:
								{
									pDeviceManager.Keyboard.bKeys[KEY_4] = false;

									break;
								}

								case 0x35:
								{
									pDeviceManager.Keyboard.bKeys[KEY_5] = false;

									break;
								}

								case 0x36:
								{
									pDeviceManager.Keyboard.bKeys[KEY_6] = false;

									break;
								}

								case 0x37:
								{
									pDeviceManager.Keyboard.bKeys[KEY_7] = false;

									break;
								}

								case 0x38:
								{
									pDeviceManager.Keyboard.bKeys[KEY_8] = false;

									break;
								}

								case 0x39:
								{
									pDeviceManager.Keyboard.bKeys[KEY_9] = false;

									break;
								}

								case 0x41:
								{
									pDeviceManager.Keyboard.bKeys[KEY_A] = false;

									break;
								}

								case 0x42:
								{
									pDeviceManager.Keyboard.bKeys[KEY_B] = false;

									break;
								}

								case 0x43:
								{
									pDeviceManager.Keyboard.bKeys[KEY_C] = false;

									break;
								}

								case 0x44:
								{
									pDeviceManager.Keyboard.bKeys[KEY_D] = false;

									break;
								}

								case 0x45:
								{
									pDeviceManager.Keyboard.bKeys[KEY_E] = false;

									break;
								}

								case 0x46:
								{
									pDeviceManager.Keyboard.bKeys[KEY_F] = false;

									break;
								}

								case 0x47:
								{
									pDeviceManager.Keyboard.bKeys[KEY_G] = false;

									break;
								}

								case 0x48:
								{
									pDeviceManager.Keyboard.bKeys[KEY_H] = false;

									break;
								}

								case 0x49:
								{
									pDeviceManager.Keyboard.bKeys[KEY_I] = false;

									break;
								}

								case 0x4A:
								{
									pDeviceManager.Keyboard.bKeys[KEY_J] = false;

									break;
								}

								case 0x4B:
								{
									pDeviceManager.Keyboard.bKeys[KEY_K] = false;

									break;
								}

								case 0x4C:
								{
									pDeviceManager.Keyboard.bKeys[KEY_L] = false;

									break;
								}

								case 0x4D:
								{
									pDeviceManager.Keyboard.bKeys[KEY_M] = false;

									break;
								}

								case 0x4E:
								{
									pDeviceManager.Keyboard.bKeys[KEY_N] = false;

									break;
								}

								case 0x4F:
								{
									pDeviceManager.Keyboard.bKeys[KEY_O] = false;

									break;
								}

								case 0x50:
								{
									pDeviceManager.Keyboard.bKeys[KEY_P] = false;

									break;
								}

								case 0x51:
								{
									pDeviceManager.Keyboard.bKeys[KEY_Q] = false;

									break;
								}

								case 0x52:
								{
									pDeviceManager.Keyboard.bKeys[KEY_R] = false;

									break;
								}

								case 0x53:
								{
									pDeviceManager.Keyboard.bKeys[KEY_S] = false;

									break;
								}

								case 0x54:
								{
									pDeviceManager.Keyboard.bKeys[KEY_T] = false;

									break;
								}

								case 0x55:
								{
									pDeviceManager.Keyboard.bKeys[KEY_U] = false;

									break;
								}

								case 0x56:
								{
									pDeviceManager.Keyboard.bKeys[KEY_V] = false;

									break;
								}

								case 0x57:
								{
									pDeviceManager.Keyboard.bKeys[KEY_W] = false;

									break;
								}

								case 0x58:
								{
									pDeviceManager.Keyboard.bKeys[KEY_X] = false;

									break;
								}

								case 0x59:
								{
									pDeviceManager.Keyboard.bKeys[KEY_Y] = false;

									break;
								}

								case 0x5A:
								{
									pDeviceManager.Keyboard.bKeys[KEY_Z] = false;

									break;
								}

								case 0x26:
								{
									pDeviceManager.Keyboard.bKeys[KEY_ARROW_UP] = false;

									break;
								}

								case 0x28:
								{
									pDeviceManager.Keyboard.bKeys[KEY_ARROW_DOWN] = false;

									break;
								}

								case 0x25:
								{
									pDeviceManager.Keyboard.bKeys[KEY_ARROW_LEFT] = false;

									break;
								}

								case 0x27:
								{
									pDeviceManager.Keyboard.bKeys[KEY_ARROW_RIGHT] = false;

									break;
								}

								case 0x20:
								{
									pDeviceManager.Keyboard.bKeys[KEY_SPACE] = false;

									break;
								}

								case 0x11:
								{
									pDeviceManager.Keyboard.bKeys[KEY_CTRL] = false;

									break;
								}
							}

							break;
						}
					}

					break;
				}
			}

			break;
		}
	}

	return DefWindowProc(hWindow, message, wParameter, lParameter);
}

LRESULT __stdcall Uniquis::Window::handleMessageThunk(HWND hWindow, UINT message, WPARAM wParameter, LPARAM lParameter) noexcept
{
	Window* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWindow, GWLP_USERDATA));

	return pWindow->handleMessage(hWindow, message, wParameter, lParameter);
}