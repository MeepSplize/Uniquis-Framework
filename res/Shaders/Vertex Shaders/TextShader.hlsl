struct CameraData
{
	float3 Position;
	float4 Rotation;
	float4 PerspectiveProjectionData;
};

ConstantBuffer<CameraData> CameraDataBuffer : register(b0);

struct VSInput
{
	float3 Position          : POSITION;
	float3 Normal            : NORMAL;
	float2 TextureCoordinate : TEXTURECOORDINATE;
};

struct VSOutput
{
	float3 WorldSpacePosition  : POSITION;
	float4 ScreenSpacePosition : SV_POSITION;
	float3 Normal              : NORMAL;
	float2 TextureCoordinate   : TEXTURECOORDINATE;
};

VSOutput main(VSInput input)
{
	VSOutput Output;

	Output.WorldSpacePosition  = input.Position;
	Output.ScreenSpacePosition = float4(((input.Position.x * (9.0f/16.0f)) - 1.0f), input.Position.y, input.Position.z, 1.0f);
	Output.Normal              = input.Normal;
	Output.TextureCoordinate   = input.TextureCoordinate;

	return Output;
}