#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\ResourceDescription.h"

template<Uniquis::DirectX12::ResourceType Type>
Uniquis::DirectX12::ResourceDescription<Type>::ResourceDescription(const unsigned __int64			                     width, 
															       const unsigned __int32			                     height, 
															       const unsigned __int16			                     depthOrArraySize,
															       const unsigned __int16			                     mipLevels,
															       const          DXGI_FORMAT&                           pFormat,
															       const          Uniquis::DirectX12::SampleDescription& pSampleDescription,
			   												       const          Uniquis::DirectX12::ClearValue*        pClearValue,
															       const          Uniquis::DirectX12::ResourceStates&    pResourceState,
															       const          Uniquis::DirectX12::ResourceCreation&  pResourceCreation,
															       const		  Uniquis::DirectX12::ResourceFlags&     pFlags)

	:  InternalDescription(),
	         ResourceState(pResourceState),
	      ResourceCreation(pResourceCreation)
{
	this->pClearValue = std::make_unique<ClearValue>(*(pClearValue));

	this->pClearValue->InternalValue.Format = pFormat;

	this->InternalDescription.Alignment        = 0;
	this->InternalDescription.Width            = width;
	this->InternalDescription.Height           = height;
	this->InternalDescription.DepthOrArraySize = depthOrArraySize;
	this->InternalDescription.MipLevels        = mipLevels;
	this->InternalDescription.Format           = pFormat;
	this->InternalDescription.SampleDesc       = **(pSampleDescription);
	this->InternalDescription.Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	this->InternalDescription.Flags            = D3D12_RESOURCE_FLAGS(pFlags);
}

template<>																																				     
Uniquis::DirectX12::ResourceDescription<Uniquis::DirectX12::ResourceType::Buffer>::ResourceDescription(const unsigned __int64			                     width, 
																								       const unsigned __int32			                     height, 
																								       const unsigned __int16			                     depthOrArraySize,
																								       const unsigned __int16			                     mipLevels,
																								       const          DXGI_FORMAT&                           pFormat,
																								       const          Uniquis::DirectX12::SampleDescription& pSampleDescription,
			   																					       const          Uniquis::DirectX12::ClearValue*        pClearValue,
																								       const          Uniquis::DirectX12::ResourceStates&    pResourceState,
																								       const          Uniquis::DirectX12::ResourceCreation&  pResourceCreation,
																								       const		  Uniquis::DirectX12::ResourceFlags&     pFlags)

	:  InternalDescription(),
	   ResourceState(pResourceState),
	   ResourceCreation(pResourceCreation)
{
	this->InternalDescription.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER;
	this->InternalDescription.Alignment        = 65536;
	this->InternalDescription.Width            = width;
	this->InternalDescription.Height           = height;
	this->InternalDescription.DepthOrArraySize = depthOrArraySize;
	this->InternalDescription.MipLevels        = mipLevels;
	this->InternalDescription.Format           = pFormat;
	this->InternalDescription.SampleDesc       = **(pSampleDescription);
	this->InternalDescription.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	this->InternalDescription.Flags            = D3D12_RESOURCE_FLAGS(pFlags);
}

template<>
Uniquis::DirectX12::ResourceDescription<Uniquis::DirectX12::ResourceType::Texture1D>::ResourceDescription(const unsigned __int64			                    width, 
																								          const unsigned __int32			                    height, 
																								          const unsigned __int16			                    depthOrArraySize,
																								          const unsigned __int16			                    mipLevels,
																								          const          DXGI_FORMAT&                           pFormat,
																								          const          Uniquis::DirectX12::SampleDescription& pSampleDescription,
			   																					          const          Uniquis::DirectX12::ClearValue*        pClearValue,
																								          const          Uniquis::DirectX12::ResourceStates&    pResourceState,
																								          const          Uniquis::DirectX12::ResourceCreation&  pResourceCreation,
																								          const		     Uniquis::DirectX12::ResourceFlags&     pFlags)

	:  InternalDescription(),
	         ResourceState(pResourceState),
	      ResourceCreation(pResourceCreation)
{
	this->pClearValue = std::make_unique<ClearValue>(*(pClearValue));

	this->pClearValue->InternalValue.Format = pFormat;

	this->InternalDescription.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE1D;
	this->InternalDescription.Alignment        = 0;
	this->InternalDescription.Width            = width;
	this->InternalDescription.Height           = height;
	this->InternalDescription.DepthOrArraySize = depthOrArraySize;
	this->InternalDescription.MipLevels        = mipLevels;
	this->InternalDescription.Format           = pFormat;
	this->InternalDescription.SampleDesc       = **(pSampleDescription);
	this->InternalDescription.Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	this->InternalDescription.Flags            = D3D12_RESOURCE_FLAGS(pFlags);
}

template<>
Uniquis::DirectX12::ResourceDescription<Uniquis::DirectX12::ResourceType::Texture2D>::ResourceDescription(const unsigned __int64			                  width, 
																								 const unsigned __int32			                  height, 
																								 const unsigned __int16			                  depthOrArraySize,
																								 const unsigned __int16			                  mipLevels,
																								 const          DXGI_FORMAT&                      pFormat,
																								 const          Uniquis::DirectX12::SampleDescription& pSampleDescription,
			   																					 const          Uniquis::DirectX12::ClearValue*        pClearValue,
																								 const          Uniquis::DirectX12::ResourceStates&    pResourceState,
																								 const          Uniquis::DirectX12::ResourceCreation&  pResourceCreation,
																								 const		    Uniquis::DirectX12::ResourceFlags&     pFlags)

	:  InternalDescription(),
	         ResourceState(pResourceState),
	      ResourceCreation(pResourceCreation)
{
	this->pClearValue = std::make_unique<ClearValue>(*(pClearValue));

	this->pClearValue->InternalValue.Format = pFormat;

	this->InternalDescription.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	this->InternalDescription.Alignment        = 0;
	this->InternalDescription.Width            = width;
	this->InternalDescription.Height           = height;
	this->InternalDescription.DepthOrArraySize = depthOrArraySize;
	this->InternalDescription.MipLevels        = mipLevels;
	this->InternalDescription.Format           = pFormat;
	this->InternalDescription.SampleDesc       = **(pSampleDescription);
	this->InternalDescription.Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	this->InternalDescription.Flags            = D3D12_RESOURCE_FLAGS(pFlags);
}

template<>
Uniquis::DirectX12::ResourceDescription<Uniquis::DirectX12::ResourceType::Texture3D>::ResourceDescription(const unsigned __int64			                  width, 
																								 const unsigned __int32			                  height, 
																								 const unsigned __int16			                  depthOrArraySize,
																								 const unsigned __int16			                  mipLevels,
																								 const          DXGI_FORMAT&                      pFormat,
																								 const          Uniquis::DirectX12::SampleDescription& pSampleDescription,
			   																					 const          Uniquis::DirectX12::ClearValue*        pClearValue,
																								 const          Uniquis::DirectX12::ResourceStates&    pResourceState,
																								 const          Uniquis::DirectX12::ResourceCreation&  pResourceCreation,
																								 const		    Uniquis::DirectX12::ResourceFlags&     pFlags)

	:  InternalDescription(),
	         ResourceState(pResourceState),
	      ResourceCreation(pResourceCreation)
{
	this->pClearValue = std::make_unique<ClearValue>(*(pClearValue));

	this->pClearValue->InternalValue.Format = pFormat;

	this->InternalDescription.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
	this->InternalDescription.Alignment        = 0;
	this->InternalDescription.Width            = width;
	this->InternalDescription.Height           = height;
	this->InternalDescription.DepthOrArraySize = depthOrArraySize;
	this->InternalDescription.MipLevels        = mipLevels;
	this->InternalDescription.Format           = pFormat;
	this->InternalDescription.SampleDesc       = **(pSampleDescription);
	this->InternalDescription.Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	this->InternalDescription.Flags            = D3D12_RESOURCE_FLAGS(pFlags);
}

template<Uniquis::DirectX12::ResourceType Type>
Uniquis::DirectX12::ResourceDescription<Type>::~ResourceDescription()
{

}

template<Uniquis::DirectX12::ResourceType Type>
const InternalResourceDescription* Uniquis::DirectX12::ResourceDescription<Type>::operator*() const noexcept
{
	return &(this->InternalDescription);
}

template class Uniquis::DirectX12::ResourceDescription<Uniquis::DirectX12::ResourceType::Buffer>;
template class Uniquis::DirectX12::ResourceDescription<Uniquis::DirectX12::ResourceType::Texture1D>;
template class Uniquis::DirectX12::ResourceDescription<Uniquis::DirectX12::ResourceType::Texture2D>;
template class Uniquis::DirectX12::ResourceDescription<Uniquis::DirectX12::ResourceType::Texture3D>;
