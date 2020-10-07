#pragma once

#include "Framework\\Include\\Include.h"

#include "Toolkit\\Include\\Include.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\General\Include.h"

namespace Uniquis
{
	enum class ApplicationType
	{
		Reactive,
		Responsive
	};

	struct ApplicationDescription
	{
	public:

		ApplicationType Type;

		HINSTANCE Handle;

		std::unique_ptr<Timer> pTRunning;

	public:

		ApplicationDescription()
		{

		}

		ApplicationDescription(const ApplicationDescription&) = delete;

		ApplicationDescription(const ApplicationDescription&&) = delete;

		~ApplicationDescription()
		{

		}

	public:

		void operator=(const ApplicationDescription&) = delete;
	};

	class Application
	{
	private:

		std::vector<std::unique_ptr<Font>> vpFonts;

		std::vector<std::unique_ptr<Text>> vpTexts;

		std::vector<std::unique_ptr<Object>> vpObjects;

		mutable unsigned __int16 FPS;

		Timer TSeconds;

		DeviceManager&   pDeviceManager   = DeviceManager::getReference();
		NetworkManager&  pNetworkManager  = NetworkManager::getReference();
		WindowManager&   pWindowManager   = WindowManager::getReference();
		GraphicsManager& pGraphicsManager = GraphicsManager::getReference();

	public:

		mutable ApplicationDescription Description;

		std::array<int, 10> Array;

		int Gesucht;

		int Links;
		int Rechts;
		int Mitte;

		int iSchritt;

		bool bOK     = false;
		bool bFertig = false;

	private:

		Application();

	public:

		Application(const Application&) = delete;

		Application(const Application&&) = delete;

		~Application();

	public:

		static Application& getReference();

		__int32 run();

		void countFPS() noexcept;
	};
}
