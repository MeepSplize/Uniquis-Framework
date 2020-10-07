#include "pch.h"

#include "Framework\\Managers\\Device Manager\\Toolkit\\Interfaces\\IDevice.h"

Uniquis::IDevice::~IDevice() 
{

}

HANDLE Uniquis::IDevice::getHandle()
{
	return this->hDevice;
}

Uniquis::IDevice::Type Uniquis::IDevice::getType()
{
	return this->tDevice;
}