#pragma once

namespace Uniquis::DirectX12
{
	class IBindable
	{
	public:

		IBindable();

		virtual ~IBindable() = 0;

	public:

		virtual void bind() = 0;
	};
}