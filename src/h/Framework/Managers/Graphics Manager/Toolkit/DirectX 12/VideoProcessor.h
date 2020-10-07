#pragma once

#include "VideoDevice.h"

namespace Uniquis::DirectX12
{
	class VideoProcessor
	{
	private:

		ID3D12VideoProcessor* pInternal;

	public:

		VideoProcessor() = delete;

		VideoProcessor(const VideoProcessor&) = delete;

		VideoProcessor(const VideoProcessor&&) = delete;

		VideoProcessor(const VideoDevice& pVideoDevice);

		~VideoProcessor();

	public:

		void operator=(const VideoProcessor&) = delete;

		ID3D12VideoProcessor* operator*()  const;
		ID3D12VideoProcessor* operator->() const;
	};
}