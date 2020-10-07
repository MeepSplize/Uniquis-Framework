#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\SampleDescription.h"

// CONSTRUCTORS

Uniquis::DirectX12::SampleDescription::SampleDescription(const unsigned __int32 count, const unsigned __int32 quality)

	: InternalDescription() 
{
	this->InternalDescription.Count   = count;
	this->InternalDescription.Quality = quality;
}

// DECONSTRUCTORS

Uniquis::DirectX12::SampleDescription::~SampleDescription()
{

}

// OPERATORS

const DXGI_SAMPLE_DESC* Uniquis::DirectX12::SampleDescription::operator*() const noexcept
{
	const DXGI_SAMPLE_DESC* pInternalDescription = &(this->InternalDescription);

	return pInternalDescription;
}