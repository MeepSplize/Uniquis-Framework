#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\PipelineState.h"

Uniquis::DirectX12::PipelineState<Uniquis::DirectX12::PipelineStateType::Rasterisation>::PipelineState(const Device& pDevice, const RootSignature& pRootSignature, const VertexShader& pVS, const GeometryShader& pGS, const PixelShader& pPS, const TopologyTypes& pTopologyType, const PipelineStateFlags& pFlags)
{
	HRESULT hResult = 0;

	//D3D12_RENDER_TARGET_BLEND_DESC RenderTargetBlendDesc = {
	//
	//	false,
	//	false,
	//	D3D12_BLEND_ONE,
	//	D3D12_BLEND_ZERO,
	//	D3D12_BLEND_OP_ADD,
	//	D3D12_BLEND_ONE,
	//	D3D12_BLEND_ZERO,
	//	D3D12_BLEND_OP_ADD,
	//	D3D12_LOGIC_OP_NOOP,
	//	D3D12_COLOR_WRITE_ENABLE_ALL
	//};

	D3D12_RENDER_TARGET_BLEND_DESC RenderTargetBlendDesc = {};

	RenderTargetBlendDesc.BlendEnable           = true;
	RenderTargetBlendDesc.LogicOpEnable         = false;
	RenderTargetBlendDesc.SrcBlend              = D3D12_BLEND_SRC_ALPHA;
	RenderTargetBlendDesc.DestBlend             = D3D12_BLEND_INV_SRC_ALPHA;
	RenderTargetBlendDesc.BlendOp               = D3D12_BLEND_OP_ADD;
	RenderTargetBlendDesc.SrcBlendAlpha         = D3D12_BLEND_ONE;
	RenderTargetBlendDesc.DestBlendAlpha        = D3D12_BLEND_ZERO;
	RenderTargetBlendDesc.BlendOpAlpha          = D3D12_BLEND_OP_ADD;
	RenderTargetBlendDesc.LogicOp               = D3D12_LOGIC_OP_NOOP;
	RenderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;


	D3D12_BLEND_DESC BlendDesc = {};

	BlendDesc.AlphaToCoverageEnable  = false;
	BlendDesc.IndependentBlendEnable = false;

	for (UINT8 i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
	{
		BlendDesc.RenderTarget[i] = RenderTargetBlendDesc;
	}

	D3D12_RASTERIZER_DESC RasterizerDesc = {
	
		D3D12_FILL_MODE_SOLID,
		D3D12_CULL_MODE_BACK,
		false,
		D3D12_DEFAULT_DEPTH_BIAS,
		D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
		true,
		false,
		false,
		0,
		D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
	};

	const D3D12_DEPTH_STENCILOP_DESC DefaultStencilOperation = {

		D3D12_STENCIL_OP_KEEP, 
		D3D12_STENCIL_OP_KEEP,
		D3D12_STENCIL_OP_KEEP, 
		D3D12_COMPARISON_FUNC_ALWAYS
	};

	D3D12_DEPTH_STENCIL_DESC DepthStencilDesc = {};

	DepthStencilDesc.DepthEnable      = true;
	DepthStencilDesc.DepthWriteMask   = D3D12_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc        = D3D12_COMPARISON_FUNC_LESS;
	DepthStencilDesc.StencilEnable    = false;
	DepthStencilDesc.StencilReadMask  = D3D12_DEFAULT_STENCIL_READ_MASK;
	DepthStencilDesc.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
	DepthStencilDesc.FrontFace        = DefaultStencilOperation;
	DepthStencilDesc.BackFace         = DefaultStencilOperation;

	D3D12_INPUT_ELEMENT_DESC InputElementDescs[] = {

		{ "POSITION",          0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL",            0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXTURECOORDINATE", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IndexBufferStripCutValueDesc = {

		D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED
	};

	DXGI_SAMPLE_DESC SampleDesc = {};

	SampleDesc.Count   = 1;
	SampleDesc.Quality = 0;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC PipelineStateDesc = {};

	PipelineStateDesc.pRootSignature		= *(pRootSignature);
	PipelineStateDesc.VS					= *(pVS);
	PipelineStateDesc.GS					= *(pGS);
	PipelineStateDesc.PS					= *(pPS);
	PipelineStateDesc.BlendState			= BlendDesc;
	PipelineStateDesc.SampleMask			= UINT_MAX;
	PipelineStateDesc.RasterizerState		= RasterizerDesc;
	PipelineStateDesc.DepthStencilState		= DepthStencilDesc;
	PipelineStateDesc.InputLayout			= { InputElementDescs, _countof(InputElementDescs) };
	PipelineStateDesc.IBStripCutValue		= IndexBufferStripCutValueDesc;
	PipelineStateDesc.NumRenderTargets		= 1;
	PipelineStateDesc.RTVFormats[0]			= DXGI_FORMAT_R8G8B8A8_UNORM;
	PipelineStateDesc.DSVFormat             = DXGI_FORMAT_D32_FLOAT;
	PipelineStateDesc.SampleDesc			= SampleDesc;
	PipelineStateDesc.NodeMask				= 0;
	PipelineStateDesc.Flags					= D3D12_PIPELINE_STATE_FLAG_NONE;
	PipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE(pTopologyType);

	hResult = pDevice->CreateGraphicsPipelineState(&(PipelineStateDesc), IID_PPV_ARGS(&(this->pPipelineState)));

	if (FAILED(hResult))
	{
		OutputDebugString(L"[ERROR] Failed to create PipelineState! \n");

		_com_error err(hResult);
		LPCTSTR errMsg = err.ErrorMessage();

		OutputDebugString(errMsg);
	}
}

Uniquis::DirectX12::PipelineState<Uniquis::DirectX12::PipelineStateType::Rasterisation>::~PipelineState()
{
	this->pPipelineState->Release();
}

ID3D12PipelineState* Uniquis::DirectX12::PipelineState<Uniquis::DirectX12::PipelineStateType::Rasterisation>::operator*() const
{
	return this->pPipelineState;
}

ID3D12PipelineState* Uniquis::DirectX12::PipelineState<Uniquis::DirectX12::PipelineStateType::Rasterisation>::operator->() const
{
	return this->pPipelineState;
}