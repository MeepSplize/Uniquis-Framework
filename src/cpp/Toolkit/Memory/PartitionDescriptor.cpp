#include "pch.h"

#include "Toolkit\\Memory\\PartitionDescriptor.h"

Uniquis::PartitionDescriptor::PartitionDescriptor()

	: Begin(0), End(0), Occupied(0)
{

}

Uniquis::PartitionDescriptor::PartitionDescriptor(const unsigned __int64 space)

	: Begin(0), End(space - 1), Occupied(0)
{

}

Uniquis::PartitionDescriptor::PartitionDescriptor(const unsigned __int64 begin, const unsigned __int64 end)

	: Begin(begin), End(end), Occupied(0)
{

}

Uniquis::PartitionDescriptor::~PartitionDescriptor()
{

}

void Uniquis::PartitionDescriptor::operator++(int) noexcept
{
	this->Occupied++;
}