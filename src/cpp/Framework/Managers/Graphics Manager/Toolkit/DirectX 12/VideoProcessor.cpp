#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\VideoProcessor.h"

Uniquis::DirectX12::VideoProcessor::VideoProcessor(const VideoDevice& pVideoDevice)
{
	D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC OutputStreamDescription = {};

	OutputStreamDescription.Format                         = DXGI_FORMAT_R8G8B8A8_UNORM;
	OutputStreamDescription.ColorSpace                     = DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709;
	OutputStreamDescription.AlphaFillMode                  = D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_OPAQUE;
	OutputStreamDescription.AlphaFillModeSourceStreamIndex = 0;
	OutputStreamDescription.BackgroundColor[0]             = 0.0f;
	OutputStreamDescription.BackgroundColor[1]             = 0.0f;
	OutputStreamDescription.BackgroundColor[2]             = 0.0f;
	OutputStreamDescription.BackgroundColor[3]             = 1.0f;
	OutputStreamDescription.FrameRate                      = { 60, 0 };
	OutputStreamDescription.EnableStereo                   = false;

	D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC InputStreamDescription = {};



	//pVideoDevice->CreateVideoProcessor(0, &(OutputStreamDescription), 1, )
}

Uniquis::DirectX12::VideoProcessor::~VideoProcessor()
{
	this->pInternal->Release();
}

ID3D12VideoProcessor* Uniquis::DirectX12::VideoProcessor::operator*() const
{
	return this->pInternal;
}

ID3D12VideoProcessor* Uniquis::DirectX12::VideoProcessor::operator->() const
{
	return this->pInternal;
}