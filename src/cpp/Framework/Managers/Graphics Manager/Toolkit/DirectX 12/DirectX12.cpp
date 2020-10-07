#include "pch.h"

#include "Project\\Macros\\Macros.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\DirectX12.h"

Uniquis::DirectX12::DirectX12::DirectX12()
{
	FactoryFlag FactoryFlags = FactoryFlag::None;

	DEBUG_ONLY
	(
		this->pDebugController = std::make_unique<DebugController>();
	
		FactoryFlags = FactoryFlag::Debug;
	);

	this->pFactory = std::make_unique<Factory>(FactoryFlags);

	this->pDevice = std::make_unique<Device>(*(this->pFactory), DeviceFlags::NONE);

	this->pVideoDevice = std::make_unique<VideoDevice>(*(this->pDevice));
	
	this->pCommandQueue = std::make_unique<CommandQueue>(*(this->pDevice), CommandQueueFlags::NONE);

	this->pFence = std::make_unique<Fence>(*(this->pDevice), FenceFlags::NONE);
}

Uniquis::DirectX12::DirectX12::~DirectX12()
{

}

void Uniquis::DirectX12::DirectX12::addWindow(const unsigned __int16 width, const unsigned __int16 height, HWND hWnd)
{
	this->vpSwapChains.reserve(1);

	this->vpSwapChains.emplace_back(std::make_unique<SwapChain>(width, height, hWnd, *(this->pFactory), *(this->pDevice), *(this->pCommandQueue), SwapChainFlags::NONE));

	this->loadAssets();
}

void Uniquis::DirectX12::DirectX12::loadAssets()
{
	/* Camera */

	this->pCamera = std::make_unique<Camera>(this->vpSwapChains[0]->Width, this->vpSwapChains[0]->Height);

	/* Root Signature */

	std::vector<RootParameter> vRootParameters;
	std::vector<StaticSampler> vStaticSamplers;

	RootConstants CameraData(0, 12);    // Register b0 | Translation, Rotation as Vector<3> (+ Padding), Quaternion

	DescriptorRange<DescriptorRangeType::ShaderResources> ShaderResourceDescriptorRange(0, 0);

	DescriptorRange<DescriptorRangeType::ConstantBuffers> ModelDataBufferDescriptorRange(1, 1);

	DescriptorRange<DescriptorRangeType::ConstantBuffers> LightDataBufferDescriptorRange(0, 0);

	RootDescriptorTable VertexShaderDescriptorTable( { 0, 0, 1, 0 },
										            nullptr,
										            nullptr,
										            &(ModelDataBufferDescriptorRange),
										            nullptr);

	RootDescriptorTable PixelShaderDescriptorTable( { 0, 0, 1, 0 },
										           nullptr,
										           nullptr,
										           &(LightDataBufferDescriptorRange),
										           nullptr);

	RootDescriptorTable Neu( { 1, 0, 0, 0 },
							&(ShaderResourceDescriptorRange),
							nullptr,
							nullptr,
							nullptr);

	vRootParameters.reserve(4);

	vRootParameters.emplace_back(CameraData, ShaderVisibility::VertexShader);

	vRootParameters.emplace_back(PixelShaderDescriptorTable, ShaderVisibility::PixelShader);

	vRootParameters.emplace_back(VertexShaderDescriptorTable, ShaderVisibility::VertexShader);

	vRootParameters.emplace_back(Neu, ShaderVisibility::PixelShader);

	vStaticSamplers.reserve(1);

	vStaticSamplers.emplace_back();

	RootSignatureDescription RootSignatureDescription(std::move(vRootParameters), std::move(vStaticSamplers));

	this->pRootSignature = std::make_unique<RootSignature>(RootSignatureDescription, *(this->pDevice));

	/* -/- */

	VertexShader VS(L"VertexShader");

	VS.compile();

	VertexShader VSText(L"TextShader"); VSText.compile();

	GeometryShader GS(L"GeometryShader");

	GS.compile();

	PixelShader PS(L"PixelShader");

	PS.compile();

	PixelShader PSText(L"TextShader"); PSText.compile();

	this->vPipelineStates.reserve(2);

	this->vPipelineStates.emplace_back(*(this->pDevice), *(this->pRootSignature), VS, nullptr, PS, TopologyTypes::TRIANGLE, PipelineStateFlags::NONE);
	this->vPipelineStates.emplace_back(*(this->pDevice), *(this->pRootSignature), VSText, nullptr, PSText, TopologyTypes::TRIANGLE, PipelineStateFlags::NONE);


	this->pCommandList = std::make_unique<CommandList>(this->vPipelineStates[0], this->vpSwapChains[0]->vCommandAllocators[0], *(this->pDevice));

	DescriptorHeapDescription DSVDescriptorHeapDescription(1, DescriptorHeapFlags::NONE);

	this->pDSVDescriptorHeap = std::make_unique<DescriptorHeap<DescriptorHeapType::DepthStencilDescriptors>>(DSVDescriptorHeapDescription, *(this->pDevice));

	this->pDepthBuffer = std::make_unique<DepthBuffer>(this->vpSwapChains[0]->Width, this->vpSwapChains[0]->Height, *(this->pDSVDescriptorHeap), *(this->pDevice));

	DescriptorHeapDescription CommonDescriptorHeapDescription(500, DescriptorHeapFlags::SHADER_VISIBILITY);

	this->pCommonDescriptorHeap = std::make_unique<DescriptorHeap<DescriptorHeapType::CommonDescriptors>>(CommonDescriptorHeapDescription, *(this->pDevice));

	this->pCommonDescriptorHeap->vPartitionDescriptors.clear();

	this->pCommonDescriptorHeap->vPartitionDescriptors.emplace_back(50);

	this->pCommonDescriptorHeap->vPartitionDescriptors.emplace_back(50, 199);

	this->pCommonDescriptorHeap->vPartitionDescriptors.emplace_back(200, 249);

	this->pCommonDescriptorHeap->vPartitionDescriptors.emplace_back(250, 299);

	this->pModelHeap = std::make_unique<ModelHeap>(10000000, *(this->pDevice));

	this->pModelHeap->add(L"Test.obj", *(this->pCommandList), *(this->pDevice));

	this->pRenderQueue = std::make_unique<RenderQueue>(this->vPipelineStates, *(this->pCommonDescriptorHeap), *(this->pModelHeap));

	const float LightColor[3]     = { 1.0f,  1.0f, 1.0f };
	const float LightDirection[3] = { 0.0f, -1.0f, 0.0f };
	const float LightPosition[3]  = { 0.0f,  0.0f, 0.0f };

	this->pLight = std::make_unique<Light<LightType::Point>>(1.0f, LightColor, LightPosition, *(this->pCommonDescriptorHeap), *(this->pCommandList), *(this->pDevice));

	// RAYTRACING 

	//this->pBottom = std::make_unique<BottomLevelAccelerationStructure>(*(this->pObject->pIndexBuffer), 
	//																   *(this->pObject->pVertexBuffer), 
	//																   *(this->pCommandList), 
	//																   *(this->pDevice));
	//
	//this->pTop = std::make_unique<TopLevelAccelerationStructure>(this->pBottom.get(), 
	//															 *(this->pCommandList), 
	//															 *(this->pDevice));
	
	/* <-------------------------------------------------------> */

	//this->vpTextures.emplace_back(std::make_unique<Texture>(L"Test.png", *(this->pCommonDescriptorHeap), *(this->pCommandList), *(this->pDevice)));

	this->pFont = std::make_unique<Font>(*(this->pCommonDescriptorHeap), *(this->pCommandList), *(this->pDevice));

	this->pCommandList->close();
	
	this->pCommandQueue->executeCommandList(*(this->pCommandList));
	
	this->pCommandQueue->signal(*(this->pFence));

	//delete imageData;
}

void Uniquis::DirectX12::DirectX12::populateCommandList(const float time, const unsigned __int8 windowIndex)
{
	this->vpSwapChains[windowIndex]->iBuffer = (*(this->vpSwapChains[windowIndex]))->GetCurrentBackBufferIndex();

	this->pFence->waitForCompletion();

	this->vpSwapChains[windowIndex]->vCommandAllocators[this->vpSwapChains[0]->iBuffer].reset();

	this->pCommandList->reset(this->vpSwapChains[windowIndex]->vCommandAllocators[this->vpSwapChains[windowIndex]->iBuffer], this->vPipelineStates[0]);
	
	for (unsigned __int32 i = 0; i < this->FunctionQueue.size(); i++)
	{
		this->FunctionQueue.front()();

		this->FunctionQueue.pop();
	}

	for (unsigned __int32 i = 0; i < this->vpObjects.size(); i++)
	{
		this->vpObjects[i]->update(*(this->pCommandList));
	}

	(*(this->pCommandList))->SetGraphicsRootSignature(**(this->pRootSignature));

	(*(this->pCommandList))->RSSetViewports(1, &(*(this->vpSwapChains[0]->Viewport)));
	(*(this->pCommandList))->RSSetScissorRects(1, &(*(this->vpSwapChains[0]->ScissorRect)));

	(*(this->pCommandList))->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->vpSwapChains[0]->vpRenderTargets[this->vpSwapChains[0]->iBuffer].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	CD3DX12_CPU_DESCRIPTOR_HANDLE RTVHandle((*(this->vpSwapChains[windowIndex]->pRTVDescriptorHeap.get()))->GetCPUDescriptorHandleForHeapStart(), this->vpSwapChains[windowIndex]->iBuffer, this->vpSwapChains[windowIndex]->pRTVDescriptorHeap->IncrementSize);

	(*(this->pCommandList))->OMSetRenderTargets(1, &(RTVHandle), false, **(this->pDepthBuffer));

	float Color[4] = { 0.25f, 0.25f, 0.25f, 1.0f };

	(*(this->pCommandList))->ClearRenderTargetView(RTVHandle, Color, 0, nullptr);

	this->pDepthBuffer->clear(*(this->pCommandList));

	/* Camera */

	DeviceManager& DM = DeviceManager::getReference();

	if (DM.Keyboard.bKeys[KEY_W])
	{
		(this->pCamera->move(std::move(Vector<3>({ 0.0f,  0.0f,  1.0f }))));

		Quaternion PlaneRotation(std::move(Vector<3>( { 0.0f, 1.0f, 0.0f } )), this->pCamera->Yaw);
	
		Vector<3> Translation({ 0.0f, 0.0f, 0.05f });

		PlaneRotation.rotateVector(Translation);

		(this->pLight->move(std::move(Translation)));
	}

	if (DM.Keyboard.bKeys[KEY_A])
	{
		(this->pCamera->move(std::move(Vector<3>({ -1.0f,  0.0f,  0.0f }))));

		Quaternion PlaneRotation(std::move(Vector<3>( { 0.0f, 1.0f, 0.0f } )), this->pCamera->Yaw);
	
		Vector<3> Translation({ -0.05f, 0.0f, 0.0f });

		PlaneRotation.rotateVector(Translation);

		(this->pLight->move(std::move(Translation)));
	}

	if (DM.Keyboard.bKeys[KEY_S])
	{
		(this->pCamera->move(std::move(Vector<3>({ 0.0f,  0.0f, -1.0f }))));

		Quaternion PlaneRotation(std::move(Vector<3>( { 0.0f, 1.0f, 0.0f } )), this->pCamera->Yaw);
	
		Vector<3> Translation({ 0.0f, 0.0f, -0.05f });

		PlaneRotation.rotateVector(Translation);

		(this->pLight->move(std::move(Translation)));
	}

	if (DM.Keyboard.bKeys[KEY_D])
	{
		(this->pCamera->move(std::move(Vector<3>({ 1.0f,  0.0f,  0.0f }))));

		Quaternion PlaneRotation(std::move(Vector<3>( { 0.0f, 1.0f, 0.0f } )), this->pCamera->Yaw);
	
		Vector<3> Translation({ 0.05f, 0.0f, 0.0f });

		PlaneRotation.rotateVector(Translation);

		(this->pLight->move(std::move(Translation)));
	}

	if (DM.Keyboard.bKeys[KEY_CTRL])
	{
		(this->pCamera->move(std::move(Vector<3>({ 0.0f, -1.0f,  0.0f }))));

		Quaternion PlaneRotation(std::move(Vector<3>( { 0.0f, 1.0f, 0.0f } )), this->pCamera->Yaw);
	
		Vector<3> Translation({ 0.0f, -0.05f, 0.0f });

		PlaneRotation.rotateVector(Translation);

		(this->pLight->move(std::move(Translation)));
	}

	if (DM.Keyboard.bKeys[KEY_SPACE])
	{
		(this->pCamera->move(std::move(Vector<3>({ 0.0f,  1.0f,  0.0f }))));

		Quaternion PlaneRotation(std::move(Vector<3>( { 0.0f, 1.0f, 0.0f } )), this->pCamera->Yaw);
	
		Vector<3> Translation({ 0.0f, 0.05f, 0.0f });

		PlaneRotation.rotateVector(Translation);

		(this->pLight->move(std::move(Translation)));
	}

	this->pCamera->rotate(static_cast<float>(DM.Mouse.y), static_cast<float>(DM.Mouse.x), 0.0f);

	this->pCamera->update();
	this->pLight->update(*(this->pCommandList));

	float RootConstants[] = {

		this->pCamera->Position.vComponents[0],      this->pCamera->Position.vComponents[1],      this->pCamera->Position.vComponents[2],      0.0f,
		this->pCamera->Rotation.Axis.vComponents[0], this->pCamera->Rotation.Axis.vComponents[1], this->pCamera->Rotation.Axis.vComponents[2], this->pCamera->Rotation.Scalar,
		this->pCamera->PerspectiveProjectionData[0], this->pCamera->PerspectiveProjectionData[1], this->pCamera->PerspectiveProjectionData[2], this->pCamera->PerspectiveProjectionData[3]
	};

	(*(this->pCommandList))->SetGraphicsRoot32BitConstants(0, 12, &(RootConstants[0]), 0);

	ID3D12DescriptorHeap* DescriptorHeaps[] = {
	
		(**(this->pCommonDescriptorHeap))
	};

	(*(this->pCommandList))->SetDescriptorHeaps(1, &(DescriptorHeaps[0]));
	
	(*(this->pCommandList))->SetGraphicsRootDescriptorTable(1, this->pCommonDescriptorHeap->getGPUHandleToDescriptor(0));

	this->pRenderQueue->render(*(this->pCommandList));

	(*(this->pCommandList))->ResourceBarrier(1, &(CD3DX12_RESOURCE_BARRIER::Transition(this->vpSwapChains[0]->vpRenderTargets[this->vpSwapChains[0]->iBuffer].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT)));
		  
	this->pCommandList->close();
}

void Uniquis::DirectX12::DirectX12::render(const float time, const unsigned __int8 windowIndex) 
{
	this->populateCommandList(time, windowIndex);

	this->pCommandQueue->executeCommandList(*(this->pCommandList));

	this->pCommandQueue->signal(*(this->pFence));
	
	this->vpSwapChains[windowIndex]->present(1);
}

void Uniquis::DirectX12::DirectX12::release()
{
	this->pCommandQueue->signal(*(this->pFence));

	this->pFence->waitForCompletion();
}

void Uniquis::DirectX12::DirectX12::bind(Uniquis::Object* pObject)
{
	this->FunctionQueue.push([this, pObject]() 
	{ 
		this->vpObjects.reserve(1);

		this->vpObjects.emplace_back(std::make_unique<Object>(pObject, *(this->pCommonDescriptorHeap), *(this->pCommandList), *(this->pDevice)));
		
		this->pRenderQueue->bind(*(this->vpObjects[this->vpObjects.size() - 1])); 
	});
}

void Uniquis::DirectX12::DirectX12::bind(Uniquis::Text* pText)
{
	this->FunctionQueue.push([this, pText]() 
	{ 
		this->vpTexts.emplace_back(std::make_unique<Text>(pText, this->vpFonts, *(this->pModelHeap), *(this->pCommonDescriptorHeap), *(this->pCommandList), *(this->pDevice)));

		this->pRenderQueue->bind(*(this->vpTexts[this->vpTexts.size() - 1])); 
	});
}

void Uniquis::DirectX12::DirectX12::bind(Uniquis::Font* pFont)
{
	this->FunctionQueue.push([this, pFont]() 
	{ 
		this->vpFonts.emplace_back(std::make_unique<Font>(*(this->pCommonDescriptorHeap), *(this->pCommandList), *(this->pDevice)));

		//this->pRenderQueue->bind(*(this->vpObjects[this->vpObjects.size() - 1])); 
	});
}