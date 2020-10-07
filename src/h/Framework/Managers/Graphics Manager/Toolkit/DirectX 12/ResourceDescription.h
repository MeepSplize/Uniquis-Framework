#pragma once

#include "Flags.h"
#include "Types.h"

#include "Device.h"
#include "SampleDescription.h"
#include "ClearValue.h"

namespace Uniquis::DirectX12
{
	enum class ResourceAlignment
	{
		Auto,   
		Small,     //  4 KB
		Medium,    // 64 KB
		Large      //  4 MB
	};

	template<ResourceType Type>
	class ResourceDescription
	{
	public:

		InternalResourceDescription InternalDescription;

		Uniquis::DirectX12::ResourceStates   ResourceState;
		Uniquis::DirectX12::ResourceCreation ResourceCreation;

		std::unique_ptr<Uniquis::DirectX12::ClearValue> pClearValue;

	public:

		ResourceDescription(const unsigned __int64			                      width, 
							const unsigned __int32			                      height, 
							const unsigned __int16			                      depthOrArraySize,
							const unsigned __int16			                      mipLevels,
							const          DXGI_FORMAT&                           format,
							const          Uniquis::DirectX12::SampleDescription& sampleDescription,
			   				const          Uniquis::DirectX12::ClearValue*        clearValue,
							const          Uniquis::DirectX12::ResourceStates&    resourceState,
							const          Uniquis::DirectX12::ResourceCreation&  resourceCreation,
							const		   Uniquis::DirectX12::ResourceFlags&     flags);

	public:

		~ResourceDescription();

	public:

		const InternalResourceDescription* operator*() const noexcept;
	};
}