#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\ScissorRect.h"

ScissorRect::ScissorRect()

	: pScissorRect(nullptr), ScissorRectStruct{ 0, 0, 0, 0 } {

	this->pScissorRect = &this->ScissorRectStruct;
}

D3D12_RECT ScissorRect::operator*() const {

	return this->ScissorRectStruct;
}

D3D12_RECT* ScissorRect::operator->() const {

	return this->pScissorRect;
}