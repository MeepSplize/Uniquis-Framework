#pragma once

#include "Types.h"

namespace Uniquis::DirectX12
{
	enum class FactoryFlag : unsigned __int8
	{
		None  = 0,
		Debug = 0x1
	}; 

	enum class DeviceFlags : unsigned __int8
	{
		NONE = 0
	};

	enum class FenceFlags : unsigned __int8
	{
		NONE = 0
	};

	enum class CommandQueueFlags : unsigned __int8
	{
		NONE = 0
	};

	enum class SwapChainFlags : unsigned __int8
	{
		NONE = 0
	};

#define RENDER_TARGET_VIEW				 (1 <<  0)

	enum class PipelineStateFlags : unsigned __int8
	{
		NONE  = 0,
		DEBUG = 0x1
	};

	enum class HeapFlags : unsigned __int16
	{
		NONE                           = 0,
		SHARED                         = 0x1,
		DENY_BUFFERS                   = 0x4,
		ALLOW_DISPLAY                  = 0x8,
		SHARED_CROSS_ADAPTER           = 0x20,
		DENY_RT_DS_TEXTURES            = 0x40,
		DENY_NON_RT_DS_TEXTURES        = 0x80,
		HARDWARE_PROTECTED             = 0x100,
		ALLOW_WRITE_WATCH              = 0x200,
		ALLOW_SHADER_ATOMICS           = 0x400,
		ALLOW_ALL_BUFFERS_AND_TEXTURES = 0,
		ALLOW_ONLY_BUFFERS             = 0xc0,
		ALLOW_ONLY_NON_RT_DS_TEXTURES  = 0x44,
		ALLOW_ONLY_RT_DS_TEXTURES      = 0x84
	};

	enum class DescriptorHeapFlags : unsigned __int8
	{
		NONE              = 0,
		SHADER_VISIBILITY = 0x1
	};

	enum class ResourceStates : unsigned __int32
	{
		COMMON                            = 0,
		VERTEX_AND_CONSTANT_BUFFER        = 0x1,
		INDEX_BUFFER                      = 0x2,
		RENDER_TARGET                     = 0x4,
		UNORDERED_ACCESS                  = 0x8,
		DEPTH_WRITE                       = 0x10,
		DEPTH_READ                        = 0x20,
		NON_PIXEL_SHADER_RESOURCE         = 0x40,
		PIXEL_SHADER_RESOURCE             = 0x80,
		STREAM_OUT                        = 0x100,
		INDIRECT_ARGUMENT                 = 0x200,
		COPY_DESTINATION                  = 0x400,
		COPY_SOURCE                       = 0x800,
		RESOLVE_DESTINATION               = 0x1000,
		RESOLVE_SOURCE                    = 0x2000,
		RAYTRACING_ACCELERATION_STRUCTURE = 0x400000,
		SHADING_RATE_SOURCE               = 0x1000000,
		GENERIC_READ                      = (((((0x1 | 0x2) | 0x40) | 0x80) | 0x200) | 0x800),
		PRESENT                           = 0,
		PREDICATION                       = 0x200,
		VIDEO_DECODE_READ                 = 0x10000,
		VIDEO_DECODE_WRITE                = 0x20000,
		VIDEO_PROCESS_READ                = 0x40000,
		VIDEO_PROCESS_WRITE               = 0x80000,
		VIDEO_ENCODE_READ                 = 0x200000,
		VIDEO_ENCODE_WRITE                = 0x800000
	};

	ENABLE_ENUM_OPERATORS(ResourceStates)

	enum class ResourceCreation
	{
		PLACED,
		RESERVED
	};

	enum class ResourceFlags : unsigned __int8
	{
		NONE	                    = 0,
        ALLOW_RENDER_TARGET	        = 0x1,
        ALLOW_DEPTH_STENCIL	        = 0x2,
        ALLOW_UNORDERED_ACCESS	    = 0x4,
        DENY_SHADER_RESOURCE	    = 0x8,
        ALLOW_CROSS_ADAPTER	        = 0x10,
        ALLOW_SIMULTANEOUS_ACCESS	= 0x20,
        VIDEO_DECODE_REFERENCE_ONLY	= 0x40
	};

	enum class CommandAllocatorFlags : unsigned __int8
	{
		NONE
	};
}