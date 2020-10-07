#pragma once

namespace Uniquis
{
	class IDevice
	{
	public:

		friend class DeviceManager;

		friend class Mouse;
		friend class Keyboard;

	public:     // Enums

		enum class Type {

			Mouse,
			Keyboard,
			Monitor
		};

	private:    // Variables and Instances

		HANDLE hDevice;

		IDevice::Type tDevice;

	public:     // Constructors and Deconstructors

		IDevice() = default;

		virtual ~IDevice() = 0;

	public:     // Functions

		HANDLE         getHandle();
		IDevice::Type  getType();
	};
}