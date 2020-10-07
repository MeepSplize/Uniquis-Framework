#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\VideoDecoderHeap.h"

Uniquis::DirectX12::VideoDecoder::VideoDecoder(const VideoDevice& pVideoDevice)
{
	D3D12_VIDEO_DECODE_CONFIGURATION ConfigurationDescription = {};

	ConfigurationDescription.DecodeProfile       = GUID(); //D3D12_VIDEO_DECODE_PROFILE_H264;
	ConfigurationDescription.BitstreamEncryption = D3D12_BITSTREAM_ENCRYPTION_TYPE_NONE;
	ConfigurationDescription.InterlaceType       = D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE_NONE;
	
	D3D12_VIDEO_DECODER_DESC InternalDescription = {};
	
	InternalDescription.NodeMask      = 0;
	InternalDescription.Configuration = ConfigurationDescription;

	pVideoDevice->CreateVideoDecoder(&(InternalDescription), __uuidof(ID3D12VideoDecoder), reinterpret_cast<void**>(&(this->pInternal)));
}

Uniquis::DirectX12::VideoDecoder::~VideoDecoder()
{
	this->pInternal->Release();
}

ID3D12VideoDecoder* Uniquis::DirectX12::VideoDecoder::operator*() const
{
	return this->pInternal;
}

ID3D12VideoDecoder* Uniquis::DirectX12::VideoDecoder::operator->() const
{
	return this->pInternal;
}