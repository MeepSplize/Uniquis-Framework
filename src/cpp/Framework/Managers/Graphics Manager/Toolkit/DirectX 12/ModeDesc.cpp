#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\ModeDesc.h"

/* --- Constructors --- */

Uniquis::DirectX12::ModeDesc::ModeDesc(const __int32 flags) 
		
	: ModeDescStruct() 
{
	if (flags == 0)
	{
		this->ModeDescStruct.Width       = 0;
		this->ModeDescStruct.Height      = 0;
		this->ModeDescStruct.RefreshRate = { 60, 1 };
	}
}

/* --- Operators --- */

DXGI_MODE_DESC Uniquis::DirectX12::ModeDesc::operator*() const 
{
	return this->ModeDescStruct;
}