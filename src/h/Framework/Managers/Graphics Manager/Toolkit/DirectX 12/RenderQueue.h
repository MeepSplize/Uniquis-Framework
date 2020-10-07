#pragma once

#include "Text.h"
#include "ModelHeap.h"
#include "Object.h"

namespace Uniquis::DirectX12
{
	class RenderQueue
	{
	private:

		ModelHeap* pModelHeap;

		std::vector<Object*> vpObjects;

		std::vector<unsigned __int16> viAppropriateBuffers;

		DescriptorHeap<DescriptorHeapType::CommonDescriptors>* pDescriptorHeap;

		std::vector<Text*> vpTexts;

		std::vector<PipelineState<PipelineStateType::Rasterisation>>* pvPipelineStates;

	public:

		RenderQueue() = delete;

		RenderQueue(std::vector<PipelineState<PipelineStateType::Rasterisation>>& pvPipelineStates, DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap, ModelHeap& pModelHeap);

		~RenderQueue();

	public:

		void bind(Text& pText);
		void bind(Object& pObject);

		void render(const CommandList& pCommandList);

	public:

		void operator=(const RenderQueue&) = delete;
	};
}