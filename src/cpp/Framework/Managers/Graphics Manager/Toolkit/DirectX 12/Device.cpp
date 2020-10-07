#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Device.h"

Uniquis::DirectX12::Device::Device(const Factory& pFactory, const DeviceFlags& pFlags)

	: RayTracingSupported()
{
	HRESULT hResult;

	IDXGIAdapter1* pTempAdapter;

	int AdapterIndex = 0;

	bool AdapterFound = false;

	/* Find first Hardware GPU that supports DirectX 12 */

	while (pFactory->EnumAdapters1(AdapterIndex, &(pTempAdapter)) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC1 AdapterDescription;

		pTempAdapter->GetDesc1(&(AdapterDescription));

		if (AdapterDescription.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) 
		{
			AdapterIndex++;

			continue;
		}

		hResult = D3D12CreateDevice(pTempAdapter, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device6), nullptr);

		if (SUCCEEDED(hResult))
		{
			AdapterFound = true;

			break;
		}
		
		AdapterIndex++;
	}

	if (AdapterFound)
	{
		/* Hardware Adapter */

		hResult = D3D12CreateDevice(pTempAdapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&(this->pDevice)));
		
		if (FAILED(hResult)) 
		{
			OutputDebugString(L"[ERROR] Device Creation Failed \n");
		}

		IDXGIAdapter4* pAdapter;

		pTempAdapter->QueryInterface(IID_PPV_ARGS(&(pAdapter)));

		pAdapter->SetVideoMemoryReservation(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, 1048576);    // Reserves 1 MB
	}
	else
	{
		OutputDebugString(L"[WARNING] Attempting to Create WARP Device \n");

		/* WARP Software Adapter */

		IDXGIAdapter* pWARP;

		hResult = (pFactory->EnumWarpAdapter(IID_PPV_ARGS(&(pWARP))));

		if (FAILED(hResult)) 
		{
			OutputDebugString(L"[ERROR] WARP Device Creation Failed \n");
		}

		D3D12CreateDevice(pWARP, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&(this->pDevice)));
	}

	/* Check Feature Support */

	D3D12_FEATURE_DATA_D3D12_OPTIONS5 FeatureOptions5 = {};

	this->pDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &(FeatureOptions5), sizeof(FeatureOptions5));

	if (FeatureOptions5.RaytracingTier != D3D12_RAYTRACING_TIER_NOT_SUPPORTED)
	{
		this->RayTracingSupported = true;

		OutputDebugString(L"[INFO] RayTracing is supported! \n");
	}
}

Uniquis::DirectX12::Device::~Device()
{
	this->pDevice->Release();
}

ID3D12Device6* Uniquis::DirectX12::Device::operator*() const
{
	return this->pDevice;
}

ID3D12Device6* Uniquis::DirectX12::Device::operator->() const
{
	return this->pDevice;
}