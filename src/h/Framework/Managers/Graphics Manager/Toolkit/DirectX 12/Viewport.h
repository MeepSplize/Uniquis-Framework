#pragma once

class Viewport {

/* --- Variables --- */

private:

	D3D12_VIEWPORT* pViewport;

	D3D12_VIEWPORT ViewportStruct;

/* --- Constructors --- */

public:

	Viewport();

/* --- Deconstructors --- */

public:

	~Viewport() = default;

/* --- Operators --- */

public:

	D3D12_VIEWPORT  operator*()  const;
	D3D12_VIEWPORT* operator->() const;
};