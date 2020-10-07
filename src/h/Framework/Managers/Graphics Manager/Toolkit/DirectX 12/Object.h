#pragma once

#include "Toolkit\\Math\\Quaternion.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\General\\Transformation.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\ConstantBuffer.h"

namespace Uniquis
{
	class Object;

	namespace DirectX12
	{
		class Object
		{
		private:

			std::unique_ptr<ConstantBuffer> pDataBuffer;

		public:

			Vector<2> Origin;

			unsigned __int32* pModelID;
			unsigned __int32* pMaterialID;

			Transformation* pTransformation;

		public:

			Object() = delete;

			Object(      DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
				   const CommandList&                                           pCommandList,
				   const Device&                                                pDevice);

			Object(      Uniquis::Object*                                       pObject,
				         DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
				   const CommandList&                                           pCommandList,
				   const Device&                                                pDevice);

			~Object();

		public:

			void bind(Uniquis::Object* pObject);

			void update(const CommandList& pCommandList);

		public:

			void operator=(const Object&) = delete;
		};
	}
}