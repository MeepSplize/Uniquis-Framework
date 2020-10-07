#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\FullscreenDesc.h"

// CONSTRUCTORS

Uniquis::DirectX12::FullscreenDesc::FullscreenDesc(const SwapChainFlags& flags) 

	: FullscreenDescStruct() 
{
	using namespace Uniquis::DirectX12;

	switch (flags)
	{
		case SwapChainFlags::NONE:
		{
			this->FullscreenDescStruct.RefreshRate		= { 60, 1 };
			this->FullscreenDescStruct.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
			this->FullscreenDescStruct.Scaling			= DXGI_MODE_SCALING_UNSPECIFIED;
			this->FullscreenDescStruct.Windowed			= true;
		}

		default:
		{
			this->FullscreenDescStruct.RefreshRate		= { 60, 1 };
			this->FullscreenDescStruct.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
			this->FullscreenDescStruct.Scaling			= DXGI_MODE_SCALING_UNSPECIFIED;
			this->FullscreenDescStruct.Windowed			= true;
		}
	}
}

// OPERATORS

DXGI_SWAP_CHAIN_FULLSCREEN_DESC Uniquis::DirectX12::FullscreenDesc::operator*() const 
{
	return this->FullscreenDescStruct;
}