#pragma once

class ScissorRect {

/* --- Variables and Instances --- */

private:

	D3D12_RECT* pScissorRect;

	D3D12_RECT ScissorRectStruct;

/* --- Constructors and Deconstructors --- */

public:

	ScissorRect();

	~ScissorRect() = default;

/* --- Operators --- */

public:

	D3D12_RECT  operator*()  const;
	D3D12_RECT* operator->() const;
};