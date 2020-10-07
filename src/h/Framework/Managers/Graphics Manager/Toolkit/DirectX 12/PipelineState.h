#pragma once

#include <WRL.h>

#include "Flags.h"
#include "Types.h"

#include "Device.h"
#include "RootSignature.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "VertexShader.h"

namespace Uniquis::DirectX12
{
	enum class PipelineStateType
	{
		Rasterisation,
		RayTracing
	};

	template<PipelineStateType Type>
	class PipelineState;

	template<>
	class PipelineState<PipelineStateType::Rasterisation>
	{
	private:

		ID3D12PipelineState* pPipelineState;

	public:

		PipelineState(const Device&             device, 
					  const RootSignature&      rootSignature, 
					  const VertexShader&       vs, 
					  const GeometryShader&     gs, 
					  const PixelShader&        ps, 
					  const TopologyTypes&      TopologyTypes, 
					  const PipelineStateFlags& flags);

	public:

		~PipelineState();

	public:

		ID3D12PipelineState* operator*()  const;
		ID3D12PipelineState* operator->() const;
	};

	template<>
	class PipelineState<PipelineStateType::RayTracing>
	{
	private:

		ID3D12StateObject* pPipelineState;

	public:

		PipelineState(const Device&             device, 
					  const RootSignature&      rootSignature, 
					  const VertexShader&       vs, 
					  const GeometryShader&     gs, 
					  const PixelShader&        ps, 
					  const TopologyTypes&      TopologyTypes, 
					  const PipelineStateFlags& flags);

	public:

		~PipelineState();

	public:

		ID3D12StateObject* operator*()  const;
		ID3D12StateObject* operator->() const;
	};
}