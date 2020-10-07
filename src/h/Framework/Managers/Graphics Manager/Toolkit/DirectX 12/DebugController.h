#pragma once

namespace Uniquis::DirectX12
{
	class DebugController
	{
	private:

		ID3D12Debug* pDebug;

	public:

		DebugController();

		~DebugController();

	public:

		ID3D12Debug* operator*()  const noexcept;
		ID3D12Debug* operator->() const noexcept;
	};
}