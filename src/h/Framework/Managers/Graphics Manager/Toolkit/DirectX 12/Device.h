#pragma once

#include <WRL.h>

#include "Flags.h"

#include "Factory.h"

namespace Uniquis::DirectX12
{
	class Device
	{
	private:

		ID3D12Device6* pDevice;

	public:

		bool RayTracingSupported;

	public:

		Device(const Factory& pFactory, const DeviceFlags& pFlags);

		~Device();

	public:

		void initialize(Factory& factory);

	public:

		ID3D12Device6* operator*()  const;
		ID3D12Device6* operator->() const;
	};
}