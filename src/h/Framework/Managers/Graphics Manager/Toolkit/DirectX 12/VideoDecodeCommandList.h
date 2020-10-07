#pragma once

#include "CommandList.h"

namespace Uniquis::DirectX12
{
	class VideoDecodeCommandList
	{
	private:

		ID3D12VideoDecodeCommandList1* pInternal;

	public:

		VideoDecodeCommandList() = delete;

		VideoDecodeCommandList(const VideoDecodeCommandList&)  = delete;

		VideoDecodeCommandList(const VideoDecodeCommandList&&) = delete;

		VideoDecodeCommandList(const CommandList& pCommandList);

		~VideoDecodeCommandList();

	public:

		void decode();

	public:

		void operator=(const VideoDecodeCommandList&) = delete;

		ID3D12VideoDecodeCommandList1* operator*()  const;
		ID3D12VideoDecodeCommandList1* operator->() const;
	};
}