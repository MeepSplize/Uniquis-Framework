#pragma once

#include "Device.h"
#include "CommandAllocator.h"
#include "PipelineState.h"
#include "Resource.h"

namespace Uniquis::DirectX12
{
	class CommandList
	{
	private:

		ID3D12GraphicsCommandList5* pCommandList;

	public:

		CommandList(const PipelineState<PipelineStateType::Rasterisation>& pPipelineState, const CommandAllocator& pCommandAllocator, const Device& pDevice);

		CommandList(CommandList&) = delete;

	public:

		~CommandList();

	public:

		void close();
		void reset(const CommandAllocator& commandAllocator, const PipelineState<PipelineStateType::Rasterisation>& pipelineState);

		template<Uniquis::DirectX12::ResourceType Type>
		void transitionResource(Uniquis::DirectX12::Resource<Type>& pResource, const Uniquis::DirectX12::ResourceStates& pResourceState) const;

	public:

		ID3D12GraphicsCommandList5* operator*()  const noexcept;
		ID3D12GraphicsCommandList5* operator->() const noexcept;
	};
}