#pragma once

#include "VideoDevice.h"

namespace Uniquis::DirectX12
{
	class VideoDecoder
	{
	private:

		ID3D12VideoDecoder* pInternal;

	public:

		VideoDecoder() = delete;

		VideoDecoder(const VideoDecoder&) = delete;

		VideoDecoder(const VideoDecoder&&) = delete;

		VideoDecoder(const VideoDevice& pVideoDevice);

		~VideoDecoder();

	public:

		void operator=(const VideoDecoder&) = delete;

		ID3D12VideoDecoder* operator*()  const;
		ID3D12VideoDecoder* operator->() const;
	};
}