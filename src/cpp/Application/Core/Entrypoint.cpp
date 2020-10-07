#include "pch.h"

#include "Application\\Core\\Application.h"

__int32 __stdcall WinMain(HINSTANCE hInstance, 
				          HINSTANCE hPreviousInstance, 
				          LPSTR     lpCommandLine, 
				          __int32	nCommandShow)
{
	Uniquis::Application& pApplication = Uniquis::Application::getReference();

	pApplication.Description.Type   = Uniquis::ApplicationType::Reactive;
	pApplication.Description.Handle = hInstance;

	return pApplication.run();
}