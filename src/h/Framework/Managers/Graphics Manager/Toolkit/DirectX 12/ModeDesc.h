#pragma once

#include "Flags.h"

namespace Uniquis::DirectX12 
{
	struct ModeDesc 
	{
	private:    // Variables

		DXGI_MODE_DESC ModeDescStruct;

	public:     // Constructors

		 ModeDesc(const __int32 flags);

	public:     // Deconstructors

		 ~ModeDesc() = default;

	public:     // Operators

		DXGI_MODE_DESC operator*() const;
	};
}