#pragma once

#include "Flags.h"

namespace Uniquis::DirectX12 
{
	struct FullscreenDesc 
	{

	// VARIABLES

	private:
		
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC FullscreenDescStruct;

	// CONSTRUCTORS

	public:

		FullscreenDesc(const SwapChainFlags& flags);

	// DECONSTRUCTORS

	public:

		~FullscreenDesc() = default;

	// OPERATORS

	public:

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC operator*() const;
	};
}