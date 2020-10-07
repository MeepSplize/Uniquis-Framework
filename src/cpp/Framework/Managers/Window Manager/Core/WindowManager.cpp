#include "pch.h"

#include "Framework\\Managers\\Window Manager\\Core\\WindowManager.h"

Uniquis::WindowManager::WindowManager()
{
	
}

Uniquis::WindowManager::~WindowManager()
{

}

Uniquis::WindowManager& Uniquis::WindowManager::getReference()
{
	static WindowManager Instance;

	return Instance;
}

const unsigned __int8 Uniquis::WindowManager::addWindow(const          wchar_t* name,
											                 unsigned __int16  x, 
											                 unsigned __int16  y, 
											                 unsigned __int16  width, 
											                 unsigned __int16  height, 
											           const          wchar_t* windowClassName, 
											           	     unsigned long     style) 
{
	this->vWindows.reserve(1);

	this->vWindows.emplace_back(name,
							    x, 
							    y, 
							    width, 
							    height, 
							    windowClassName,
							    style);

	const unsigned __int8 WindowIndex = (this->vWindows.size() - 1);

	return std::move(WindowIndex);
}

void Uniquis::WindowManager::addWindowClass(const WCHAR* name)
{
	this->vWindowClasses.reserve(1);

	this->vWindowClasses.emplace_back(name);
}

void Uniquis::WindowManager::addWindowClass(const wchar_t* name,
								           const __int32  icon) 
{
	this->vWindowClasses.reserve(1);

	this->vWindowClasses.emplace_back(name, icon);
}