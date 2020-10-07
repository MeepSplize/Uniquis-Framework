#include "pch.h"

#include "Framework\\Managers\\Device Manager\\Core\\DeviceManager.h"

Uniquis::DeviceManager::DeviceManager()
	
	:    Mouse(),
	  Keyboard(),
	   Monitor(0, 0)
{
	this->registerDevices();

	this->enableRawInput();
}

Uniquis::DeviceManager::~DeviceManager()
{

}

Uniquis::DeviceManager& Uniquis::DeviceManager::getReference()
{
	static DeviceManager Instance;

	return Instance;
}

void Uniquis::DeviceManager::registerDevices() 
{
	/* Monitor */

	MONITORINFOEX MonitorInfo = {};

	MonitorInfo.cbSize = sizeof(MonitorInfo);
	
	GetMonitorInfo(MonitorFromWindow(GetActiveWindow(), MONITOR_DEFAULTTONEAREST), &(MonitorInfo));

	this->Monitor.Width  = (MonitorInfo.rcMonitor.right  - MonitorInfo.rcMonitor.left);
	this->Monitor.Height = (MonitorInfo.rcMonitor.bottom - MonitorInfo.rcMonitor.top);

	/* Keyboard / Mouse */

	std::vector<RAWINPUTDEVICELIST> DeviceLists;

	unsigned __int32 nDevices = 0;

	GetRawInputDeviceList(nullptr, &(nDevices), sizeof(RAWINPUTDEVICELIST));

	if (nDevices == 0) 
	{
		return;
	}
	else 
	{
		DeviceLists.resize(nDevices);

		GetRawInputDeviceList(&(DeviceLists[0]), &(nDevices), sizeof(RAWINPUTDEVICELIST));
	}

	std::vector<char> DeviceNameData;

	UINT cCharacters = 0;

	for (unsigned __int8 i = 0; i < nDevices; i++) 
	{
		const RAWINPUTDEVICELIST& Device = DeviceLists[i];

		if (Device.dwType == RIM_TYPEMOUSE) 
		{
			GetRawInputDeviceInfo(Device.hDevice, RIDI_DEVICENAME, nullptr, &(cCharacters));

			if (cCharacters > 0) 
			{
				//DeviceNameData.resize(cCharacters);

				//GetRawInputDeviceInfo(Device.hDevice, RIDI_DEVICENAME, &DeviceNameData[0], &(cCharacters));

				//this->pDevices.reserve(1);
				//
				//this->pDevices.emplace_back(std::make_unique<Mouse>(Device.hDevice));

				//this->DeviceHandles.push_back(Device.hDevice);
				//this->DeviceNames.push_back(std::string(DeviceNameData.begin(), DeviceNameData.end()));
				//this->DeviceTypes.push_back(IDevice::Type::Mouse);
			}
		}

		if (Device.dwType == RIM_TYPEKEYBOARD) 
		{
			GetRawInputDeviceInfo(Device.hDevice, RIDI_DEVICENAME, nullptr, &(cCharacters));

			if (cCharacters > 0) 
			{
				//DeviceNameData.resize(cCharacters);

				//GetRawInputDeviceInfo(Device.hDevice, RIDI_DEVICENAME, &DeviceNameData[0], &(cCharacters));

				//this->pDevices.reserve(1);

				//this->pDevices.emplace_back(std::make_unique<Keyboard>(Device.hDevice));

				//this->DeviceHandles.push_back(Device.hDevice);
				//this->DeviceNames.push_back(std::string(DeviceNameData.begin(), DeviceNameData.end()));
				//this->DeviceTypes.push_back(IDevice::Type::Keyboard);
			}
		}
	}
}

void Uniquis::DeviceManager::enableRawInput() 
{
	RAWINPUTDEVICE RID[2];

	/* Mice */

	RID[0].usUsagePage = 0x01;
	RID[0].usUsage = 0x02;
	RID[0].dwFlags = 0; // RIDEV_NOLEGACY;    // Don't send normal, non-raw messages
	RID[0].hwndTarget = nullptr;

	/* Keyboard */

	RID[1].usUsagePage = 0x01;
	RID[1].usUsage = 0x06;
	RID[1].dwFlags = RIDEV_NOLEGACY;    // Don't send normal, non-raw messages
	RID[1].hwndTarget = nullptr;

	if (RegisterRawInputDevices(RID, 2, sizeof(RID[0])) == FALSE) 
	{
		OutputDebugString(L"[ERROR] Registration of devices failed! \n");
	}
}