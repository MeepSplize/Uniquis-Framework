#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Light.h"

Uniquis::DirectX12::Light<Uniquis::DirectX12::LightType::Ambient>::Light(const float                                             intensity,
															   const float                                             color[3],
			                                                         DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			                                                   const CommandList&                                      pCommandList,
			                                                   const Device&                                           pDevice)
{
	std::vector<float> vData;

	vData.reserve(5);

	vData.push_back(color[0]);
	vData.push_back(color[1]);
	vData.push_back(color[2]);
	vData.emplace_back(0.0f);

	vData.push_back(intensity);

	this->pDataBuffer = std::make_unique<ConstantBuffer>(std::move(vData), pDescriptorHeap, pCommandList, pDevice);

	this->pDataBuffer->bind(0, pDescriptorHeap, pDevice);
}

Uniquis::DirectX12::Light<Uniquis::DirectX12::LightType::Directional>::Light(const float                                             intensity, 
																   const float                                             color[3],
			                                                       const float                                             direction[3],
			                                                             DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			                                                       const CommandList&                                      pCommandList,
			                                                       const Device&                                           pDevice)
{
	std::vector<float> vData;

	vData.reserve(9);

	vData.push_back(color[0]);
	vData.push_back(color[1]);
	vData.push_back(color[2]);
	vData.emplace_back(0.0f);

	vData.push_back(direction[0]);
	vData.push_back(direction[1]);
	vData.push_back(direction[2]);
	vData.emplace_back(0.0f);

	vData.push_back(intensity);

	this->pDataBuffer = std::make_unique<ConstantBuffer>(std::move(vData), pDescriptorHeap, pCommandList, pDevice);

	this->pDataBuffer->bind(0, pDescriptorHeap, pDevice);
}

Uniquis::DirectX12::Light<Uniquis::DirectX12::LightType::Point>::Light(const float                                             intensity, 
															 const float                                             color[3],
			                                                 const float                                             position[3],
			                                                       DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			                                                 const CommandList&                                      pCommandList,
			                                                 const Device&                                           pDevice)
{
	std::vector<float> vData;

	vData.reserve(9);

	vData.push_back(color[0]);
	vData.push_back(color[1]);
	vData.push_back(color[2]);
	vData.emplace_back(0.0f);

	vData.push_back(position[0]);
	vData.push_back(position[1]);
	vData.push_back(position[2]);
	vData.emplace_back(0.0f);

	vData.push_back(intensity);

	this->pDataBuffer = std::make_unique<ConstantBuffer>(std::move(vData), pDescriptorHeap, pCommandList, pDevice);

	this->pDataBuffer->bind(0, pDescriptorHeap, pDevice);
}

Uniquis::DirectX12::Light<Uniquis::DirectX12::LightType::Spot>::Light(const float                                             intensity, 
															const float                                             color[3],
			                                                const float                                             direction[3], 
			                                                const float                                             position[3],
			                                                      DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			                                                const CommandList&                                      pCommandList,
			                                                const Device&                                           pDevice)
{
	std::vector<float> vData;

	vData.reserve(13);

	vData.push_back(color[0]);
	vData.push_back(color[1]);
	vData.push_back(color[2]);
	vData.emplace_back(0.0f);

	vData.push_back(direction[0]);
	vData.push_back(direction[1]);
	vData.push_back(direction[2]);
	vData.emplace_back(0.0f);

	vData.push_back(position[0]);
	vData.push_back(position[1]);
	vData.push_back(position[2]);
	vData.emplace_back(0.0f);

	vData.push_back(intensity);

	this->pDataBuffer = std::make_unique<ConstantBuffer>(std::move(vData), pDescriptorHeap, pCommandList, pDevice);

	this->pDataBuffer->bind(0, pDescriptorHeap, pDevice);
}

void Uniquis::DirectX12::Light<Uniquis::DirectX12::LightType::Point>::move(Vector<3> translation)
{
	this->pDataBuffer->vData[4] += translation.vComponents[0];
	this->pDataBuffer->vData[5] += translation.vComponents[1];
	this->pDataBuffer->vData[6] += translation.vComponents[2];
}

void Uniquis::DirectX12::Light<Uniquis::DirectX12::LightType::Point>::update(const CommandList& pCommandList)
{
	this->pDataBuffer->update(pCommandList);
}