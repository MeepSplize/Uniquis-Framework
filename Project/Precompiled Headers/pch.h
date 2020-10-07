#pragma once

#include "..\\Config\\TargetVer.h"

// ARCHITECTURE

#include <immintrin.h>

// STANDARD LIBRARY

#include <Thread>
#include <Memory>
#include <Chrono>
#include <Queue>
#include <Vector>
#include <Array>
#include <FStream>
#include <SSTream>
#include <String>
#include <Utility>
#include <Iterator>
#include <Functional>
#include <Optional>
#include <Random>

// WINDOWS

#define STRICT
#define UNICODE
#define NOMINMAX

#ifndef FULL_WINDOWS

	#define WIN32_LEAN_AND_MEAN
	#define NOGDICAPMASKS
	#define NOSYSMETRICS
	#define NOMENUS
	#define NOICONS
	#define NOSYSCOMMANDS
	#define NORASTEROPS
	#define OEMRESOURCE
	#define NOATOM
	#define NOCLIPBOARD
	#define NOCOLOR
	#define NOCTLMGR
	#define NODRAWTEXT
	#define NOKERNEL
	#define NONLS
	#define NOMEMMGR
	#define NOMETAFILE
	#define NOOPENFILE
	#define NOSCROLL
	#define NOSERVICE
	#define NOSOUND
	#define NOTEXTMETRIC
	#define NOWH
	#define NOCOMM
	#define NOKANJI
	#define NOHELP
	#define NOPROFILER
	#define NODEFERWINDOWPOS
	#define NOMCX
	#define NORPC
	#define NOPROXYSTUB
	#define NOIMAGE
	#define NOTAPE

#endif

#include <Windows.h>

#include <Winsock2.h>
#include <WRL.h>
#include <WinCodec.h>

/* Undefines */

#define UNDEFINED_GENERIC_READ (0x80000000L)

#undef GENERIC_READ

// DIRECTX

#ifdef DIRECTX_VERSION_11

	#include <D3D11.h>
	#include <DXGI.h>
	#include <D3DCompiler.h>
	#include <DirectXMath.h>

#endif

#ifdef DIRECTX_VERSION_12

	#include <D3D12.h>
	#include <D3D12Video.h>
	#include <DXGI1_6.h>
	#include <D3DCompiler.h>
	#include <DXCApi.h>
	#include <DirectXMath.h>
	
	#include "Toolkit\\Helper\D3DX12.h"

	using InternalHeapDescription             = D3D12_HEAP_DESC;
	using InternalResourceDescription         = D3D12_RESOURCE_DESC;
	using ResourceAllocationInformation       = D3D12_RESOURCE_ALLOCATION_INFO;
	using DepthStencilViewDescription         = D3D12_DEPTH_STENCIL_VIEW_DESC;
	using ConstantBufferDescriptorDescription = D3D12_CONSTANT_BUFFER_VIEW_DESC;
	using VertexBufferDescriptor              = D3D12_VERTEX_BUFFER_VIEW;
	using IndexBufferDescriptor               = D3D12_INDEX_BUFFER_VIEW;
	using SubresourceData                     = D3D12_SUBRESOURCE_DATA;
	using InternalResourceBarrier             = D3D12_RESOURCE_BARRIER;

#endif

// FILE FORMAT SUPPORT

#include "Assimp\\Importer.hpp"
#include "Assimp\\Scene.h"
#include "Assimp\\Postprocess.h"

// CONSTANTS

inline constexpr double Pi = 3.14159265358979323846;

#define KEY_0 0
#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_4 4
#define KEY_5 5
#define KEY_6 6
#define KEY_7 7
#define KEY_8 8
#define KEY_9 9
#define KEY_A 10
#define KEY_B 11
#define KEY_C 12
#define KEY_D 13
#define KEY_E 14
#define KEY_F 15
#define KEY_G 16
#define KEY_H 17
#define KEY_I 18
#define KEY_J 19
#define KEY_K 20
#define KEY_L 21
#define KEY_M 22
#define KEY_N 23
#define KEY_O 24
#define KEY_P 25
#define KEY_Q 26
#define KEY_R 27
#define KEY_S 28
#define KEY_T 29
#define KEY_U 30
#define KEY_V 31
#define KEY_W 32
#define KEY_X 33
#define KEY_Y 34
#define KEY_Z 35
#define KEY_ARROW_UP    36
#define KEY_ARROW_DOWN  37
#define KEY_ARROW_LEFT  38
#define KEY_ARROW_RIGHT 39
#define KEY_SPACE 40
#define KEY_CTRL  41

#include <Comdef.h>