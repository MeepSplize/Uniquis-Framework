#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Viewport.h"

Viewport::Viewport()

	: pViewport(nullptr), ViewportStruct{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f } {

	this->pViewport = &this->ViewportStruct;
}

D3D12_VIEWPORT* Viewport::operator->() const {

	return this->pViewport;
}

D3D12_VIEWPORT Viewport::operator*() const {

	return this->ViewportStruct;
}