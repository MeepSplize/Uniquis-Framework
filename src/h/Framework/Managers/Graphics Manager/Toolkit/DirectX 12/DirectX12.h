#pragma once

#include "Framework\\Managers\\Device Manager\\Core\\DeviceManager.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\Interfaces\\IGraphics.h"

#include "Toolkit\\Include\\Include.h"

#include "Camera.h"

#include "Include.h"

namespace Uniquis::DirectX12
{
	class DirectX12 : public IGraphics 
	{
	private:

		std::unique_ptr<TopLevelAccelerationStructure>    pTop;
		std::unique_ptr<BottomLevelAccelerationStructure> pBottom;

		/* <--- TEST ---> */

		std::unique_ptr<DepthBuffer> pDepthBuffer;

		std::unique_ptr<DescriptorHeap<DescriptorHeapType::DepthStencilDescriptors>> pDSVDescriptorHeap;

		std::unique_ptr<DescriptorHeap<DescriptorHeapType::CommonDescriptors>> pCommonDescriptorHeap;

		/* </> */

		std::unique_ptr<DebugController> pDebugController;
		std::unique_ptr<Factory>	     pFactory;
		std::unique_ptr<Device>		     pDevice;
		std::unique_ptr<CommandQueue>    pCommandQueue;
		std::unique_ptr<CommandList>     pCommandList;
		std::unique_ptr<RenderQueue>     pRenderQueue;
		std::unique_ptr<RootSignature>   pRootSignature;

		std::unique_ptr<VideoDevice>     pVideoDevice;

		std::vector<std::unique_ptr<SwapChain>> vpSwapChains;

		std::vector<PipelineState<PipelineStateType::Rasterisation>> vPipelineStates;

		std::unique_ptr<Heap<HeapType::Default>> pDefaultHeap;

		std::unique_ptr<Fence> pFence;

		// TEXTURE

		Microsoft::WRL::ComPtr<ID3D12Resource> pTextureBuffer;

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> pMainDescriptorHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource>       pTextureBufferUploadHeap;

		std::unique_ptr<ModelHeap> pModelHeap;

		std::vector<ConstantBuffer> vObjectTransformationConstantBuffers;

		std::unique_ptr<Camera> pCamera;

		std::unique_ptr<Light<LightType::Point>> pLight;

		std::vector<std::unique_ptr<Font>>   vpFonts;
		std::vector<std::unique_ptr<Text>>   vpTexts;
		std::vector<std::unique_ptr<Object>> vpObjects;

		std::queue<std::function<void()>> FunctionQueue;

		std::vector<std::unique_ptr<Texture>> vpTextures;

		std::unique_ptr<Font> pFont;

	public:

		DirectX12();

		DirectX12(const DirectX12&) = delete;

		~DirectX12();

	public:

		void addWindow(const unsigned __int16 width, const unsigned __int16 height, HWND hWnd);
		void loadAssets();
		void populateCommandList(const float time, const unsigned __int8 windowIndex);
		void render(const float time, const unsigned __int8 windowIndex);

		void release();

		void bind(Uniquis::Font*   pFont);
		void bind(Uniquis::Text*   pText);
		void bind(Uniquis::Object* pObject);

	public:

		void operator=(const DirectX12&) = delete;
	};
}