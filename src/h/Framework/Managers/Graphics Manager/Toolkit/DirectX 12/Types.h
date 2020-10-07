#pragma once

namespace Uniquis::DirectX12
{
	template<typename Enum>  
	struct EnableBitMaskOperators  
	{
	    static const bool bEnable = false;
	};

	#define ENABLE_ENUM_OPERATORS(x)      \
										  \
	template<>							  \
	struct EnableBitMaskOperators<x>	  \
	{									  \
	    static const bool bEnable = true; \
	};												
	
	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::bEnable, Enum>::type operator|(Enum First, Enum Second)
	{
		using UnderlyingType = typename std::underlying_type<Enum>::type;

		return static_cast<Enum>(static_cast<UnderlyingType>(First) | static_cast<UnderlyingType>(Second));
	}

	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::bEnable, Enum>::type operator&(Enum First, Enum Second)
	{
		using UnderlyingType = typename std::underlying_type<Enum>::type;

		return static_cast<Enum>(static_cast<UnderlyingType>(First) & static_cast<UnderlyingType>(Second));
	}

	/*----------------------------------------*/

	enum class HeapType : unsigned __int8
	{
		Default,
		Upload,
		Readback,
		Custom
	};

	enum class TopologyTypes : unsigned char
	{
		UNKNOWN,
		POINT,
		LINE,
		TRIANGLE,
		PATCH
	};

	enum class ResourceType : unsigned __int8
	{
		Buffer,
		Texture1D,
		Texture2D,
		Texture3D
	};

	enum class ShaderVisibility : unsigned __int8
	{
		All            = 0,
		VertexShader   = 1,
		HullShader     = 2,
		DomainShader   = 3,
		GeometryShader = 4,
		PixelShader    = 5
	};

	ENABLE_ENUM_OPERATORS(ShaderVisibility)
}