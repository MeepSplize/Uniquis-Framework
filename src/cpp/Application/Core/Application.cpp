#include "pch.h"

#include "bin\\Include\\FreeType\\ft2build.h"
#include FT_FREETYPE_H

#include "Application\\Core\\Application.h"

BOOL __stdcall WallpaperEnumWindowsProcess(HWND hWindow, LPARAM lParameter) 
{
	HWND WindowHandle = FindWindowExW(hWindow, 0, L"SHELLDLL_DefView", 0);

	HWND* WorkerWHandlePointer = reinterpret_cast<HWND*>(lParameter);

	if (WindowHandle)
	{
		*WorkerWHandlePointer = FindWindowExW(0, hWindow, L"WorkerW", 0);
	}

	return true;
}

HWND GetWallpaperWindowHandle()
{
	HWND ProgMan = FindWindowW(L"ProgMan", 0);

	/* Spawn a WorkerW Window */

	SendMessageTimeoutW(ProgMan, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);

	HWND hWallpaperWindow = nullptr;

	EnumWindows(WallpaperEnumWindowsProcess, reinterpret_cast<LPARAM>(&(hWallpaperWindow)));

	return hWallpaperWindow;
}

Uniquis::Application::Application()

	:      FPS(0),
	  TSeconds()
{
	bool Fullscreen = true;

	this->pWindowManager.addWindowClass(L"Application");

	if (Fullscreen)
	{
		this->pWindowManager.addWindow(L"Project",
									   0, 0,
									   this->pDeviceManager.Monitor.Width, this->pDeviceManager.Monitor.Height,
									   L"Application",
									   0);
	}
	else
	{
		this->pWindowManager.addWindow(L"Project",
							           0, 0,
							           500, 500,
							           L"Application",
							           WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU);
	}

	this->pNetworkManager.createSocket(NetworkProtocol::UDP);

	this->vpObjects.reserve(26);

	for (unsigned __int8 i = 0; i < 1; i++)
	{
		this->vpObjects.emplace_back(std::make_unique<Object>(0));

		this->vpObjects[i]->move(Vector<3>({ i * 3.0f, 0.0f, 0.0f }));

		this->vpObjects[i]->bind(this->pGraphicsManager);
	}

	this->vpFonts.emplace_back(std::make_unique<Font>());

	this->vpFonts[0]->bind(this->pGraphicsManager);

	this->vpTexts.emplace_back(std::make_unique<Text>(std::wstring(L"Hallo")));

	this->vpTexts[0]->bind(this->pGraphicsManager);
}

Uniquis::Application::~Application()
{

}

Uniquis::Application& Uniquis::Application::getReference()
{
	static Application Instance;

	return Instance;
}

__int32 Uniquis::Application::run()
{
	//SetParent(this->pWindowManager->vWindows[0].hWindow, GetWallpaperWindowHandle());

	this->Description.pTRunning = std::make_unique<Timer>();

	while (true) 
	{
		if (const std::optional<__int32> ExitCode = this->pWindowManager.vWindows[0].processMessages()) 
		{
			this->pGraphicsManager.release();

			return *(ExitCode);
		}
		
		this->pGraphicsManager.render(this->Description.pTRunning->getDuration().count(), 0);

		this->countFPS();

		this->pDeviceManager.Mouse.x = 0;
		this->pDeviceManager.Mouse.y = 0;

		//if (this->pDeviceManager.Keyboard.bKeys[8])	/* If "1" is pressed */
		//{
		//	this->pNetworkManager.sendTo(std::wstring(L"127.0.0.1"));
		//}
		//
		//if (this->pDeviceManager.Keyboard.bKeys[9])	/* If "2" is pressed */
		//{
		//	this->pNetworkManager.receiveFrom(std::wstring(L"127.0.0.1"));
		//}
	}
}

void Uniquis::Application::countFPS() noexcept 
{
	this->FPS++;

	if (this->TSeconds.getDuration() > std::chrono::duration<float>(1.0f)) 
	{
		this->pWindowManager.vWindows[0].setTitle(std::wstring(L"Test | ").append(std::to_wstring(this->FPS)).append(L" FPS").c_str());

		this->FPS = 0;

		this->TSeconds.reset();
	}
}
