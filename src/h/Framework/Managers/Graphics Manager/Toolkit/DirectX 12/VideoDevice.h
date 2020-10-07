#pragma once

#include "Device.h"

namespace Uniquis::DirectX12
{
	class VideoDevice
	{
	private:

		ID3D12VideoDevice1* pInternal;

	public:

		VideoDevice() = delete;

		VideoDevice(const VideoDevice&) = delete;

		VideoDevice(const VideoDevice&&) = delete;

		VideoDevice(const Device& pDevice);

		~VideoDevice();

	public: 

		void operator=(const VideoDevice&) = delete;

		ID3D12VideoDevice1* operator*()  const;
		ID3D12VideoDevice1* operator->() const;
	};
}