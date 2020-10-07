#pragma once

namespace Uniquis
{
	class PartitionDescriptor
	{
	public:

		unsigned __int64 Begin;
		unsigned __int64 End;

		unsigned __int64 Occupied;

	public:

		PartitionDescriptor();

		PartitionDescriptor(const unsigned __int64 space);

		PartitionDescriptor(const unsigned __int64 begin, const unsigned __int64 end);

		~PartitionDescriptor();

	public:

		void operator=(const PartitionDescriptor&) = delete;

		void operator++(int) noexcept;
	};
}