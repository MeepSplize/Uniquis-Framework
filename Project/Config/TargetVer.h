#pragma once

#include "Config.h"

#if   (WINDOWS_VERSION ==  7)

	#define WINVER       0x0601
	#define _WIN32_WINNT 0x0601

	#define DIRECTX_VERSION_11

#elif (WINDOWS_VERSION ==  8)

	#define WINVER       0x0602
	#define _WIN32_WINNT 0x0602

	#define DIRECTX_VERSION_11

#elif (WINDOWS_VERSION == 10)

	#define WINVER       0x0A00
	#define _WIN32_WINNT 0x0A00

	#define DIRECTX_VERSION_12

#endif

#include <SDKDDKVer.h>