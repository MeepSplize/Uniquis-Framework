#pragma once

#include "Flags.h"

namespace Uniquis::DirectX12
{
	class Factory
	{
	private:

		IDXGIFactory7* pFactory;

	public:

		Factory() = delete;

		Factory(const FactoryFlag& pFlags);

		~Factory();

	public:

		IDXGIFactory7* operator*()  const noexcept;
		IDXGIFactory7* operator->() const noexcept;
	};
}