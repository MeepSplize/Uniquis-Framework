#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\ClearValue.h"

Uniquis::DirectX12::ClearValue::ClearValue(const std::initializer_list<float> colorValues)

	: InternalValue()
{
	for (unsigned __int8 i = 0; i < 4; i++)
	{
		this->InternalValue.Color[i] = colorValues.begin()[i];
	}
}

Uniquis::DirectX12::ClearValue::ClearValue(float color[4])

	: InternalValue()
{
	for (unsigned __int8 i = 0; i < 4; i++)
	{
		this->InternalValue.Color[i] = color[i];
	}
}

Uniquis::DirectX12::ClearValue::ClearValue(float depthValue, unsigned __int8 stencilValue)

	: InternalValue()
{
	this->InternalValue.DepthStencil.Depth   = depthValue;
	this->InternalValue.DepthStencil.Stencil = stencilValue;
}

Uniquis::DirectX12::ClearValue::~ClearValue()
{

}

D3D12_CLEAR_VALUE* Uniquis::DirectX12::ClearValue::operator*() noexcept
{
	D3D12_CLEAR_VALUE* pClearValue = &(this->InternalValue);

	return pClearValue;
}