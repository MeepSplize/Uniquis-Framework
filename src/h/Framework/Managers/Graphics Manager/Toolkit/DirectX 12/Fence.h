#pragma once

#include <WRL.h>

#include "Flags.h"

#include "Device.h"

namespace Uniquis::DirectX12
{
	class Fence
	{
		/* --- Variables --- */

	private:

		Microsoft::WRL::ComPtr<ID3D12Fence> pFence;

	public:

		HANDLE FenceEvent;
		UINT64 ExpectedValue;

		/* --- Constructors --- */

	public:

		Fence(const Device& device, const FenceFlags& flags);

		/* --- Deconstructors --- */

		~Fence();

		/* --- Functions --- */

	public:

		void signal(UINT64 value);
		bool completed() const;
		void waitForCompletion();

		/* --- Operators --- */

	public:

		ID3D12Fence* operator*() const;
		UINT64& operator++();
		UINT64  operator++(int);
	};
}