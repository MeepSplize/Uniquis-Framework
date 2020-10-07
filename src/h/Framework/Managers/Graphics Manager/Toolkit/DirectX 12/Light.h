#pragma once

#include "Toolkit\\Math\\Vector.h"

#include "Device.h"
#include "CommandList.h"
#include "DescriptorHeap.h"
#include "ConstantBuffer.h"

namespace Uniquis::DirectX12
{
	enum class LightType
	{
		Ambient,
		Directional,
		Point,
		Spot
	};

	template<LightType Type>
	class Light;

	template<>
	class Light<LightType::Ambient>
	{
	public:

		std::unique_ptr<ConstantBuffer> pDataBuffer;

	public:

		Light() = delete;

		Light(const Light&) = delete;

		Light(const Light&&) = delete;

		Light(const float                                             intensity,
			  const float                                             color[3],
			        DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			  const CommandList&                                      pCommandList,
			  const Device&                                           pDevice);

		~Light() = default;
	};

	template<>
	class Light<LightType::Directional>
	{
	public:

		std::unique_ptr<ConstantBuffer> pDataBuffer;

	public:

		Light() = delete;

		Light(const Light&) = delete;

		Light(const Light&&) = delete;

		Light(const float                                             intensity, 
			  const float                                             color[3],
			  const float                                             direction[3],
			        DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			  const CommandList&                                      pCommandList,
			  const Device&                                           pDevice);

		~Light() = default;
	};

	template<>
	class Light<LightType::Point>
	{
	public:

		std::unique_ptr<ConstantBuffer> pDataBuffer;

	public:

		Light() = delete;

		Light(const Light&) = delete;

		Light(const Light&&) = delete;

		Light(const float                                             intensity, 
			  const float                                             color[3],
			  const float                                             position[3],
			        DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			  const CommandList&                                      pCommandList,
			  const Device&                                           pDevice);

		~Light() = default;

	public:

		void update(const CommandList& pCommandList);

		void move(Vector<3> translation);
	};

	template<>
	class Light<LightType::Spot>
	{
	public:

		std::unique_ptr<ConstantBuffer> pDataBuffer;

	public:

		Light() = delete;

		Light(const Light&) = delete;

		Light(const Light&&) = delete;

		Light(const float                                             intensity, 
			  const float                                             color[3],
			  const float                                             direction[3], 
			  const float                                             position[3],
			        DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
			  const CommandList&                                      pCommandList,
			  const Device&                                           pDevice);

		~Light() = default;
	};
}