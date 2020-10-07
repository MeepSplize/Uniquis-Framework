#pragma once

#include "Flags.h"

namespace Uniquis::DirectX12 
{
	struct SampleDescription
	{

// VARIABLES

	public:

		DXGI_SAMPLE_DESC InternalDescription;

// CONSTRUCTORS

	public:

		 SampleDescription(const unsigned __int32 count, const unsigned __int32 quality);

// DECONSTRUCTORS

	public:

		~SampleDescription();

// OPERATORS

	public:

		const DXGI_SAMPLE_DESC* operator*() const noexcept;
	};
}