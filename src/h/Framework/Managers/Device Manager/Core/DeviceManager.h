#pragma once

#include "..\\Toolkit\\Interfaces\\IDevice.h"

#include "..\\Toolkit\\General\\Keyboard.h"
#include "..\\Toolkit\\General\\Monitor.h"
#include "..\\Toolkit\\General\\Mouse.h"

namespace Uniquis
{
	class DeviceManager
	{
	public:

		Mouse    Mouse;
		Keyboard Keyboard;
		Monitor  Monitor;

		//std::vector<std::unique_ptr<IDevice>> pDevices;

	private:

		DeviceManager();

	public:

		DeviceManager(const DeviceManager&) = delete;

		~DeviceManager();

	public:

		static DeviceManager& getReference();

		void registerDevices();

		void enableRawInput();

	public:

		void operator=(const DeviceManager&) = delete;
	};
}