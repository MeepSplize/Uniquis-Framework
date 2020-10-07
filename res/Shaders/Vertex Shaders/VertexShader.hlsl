struct CameraData
{
	float3 Position;
	float4 Rotation;
	float4 PerspectiveProjectionData;
};

ConstantBuffer<CameraData> CameraDataBuffer : register(b0);

struct ModelData
{
	float3 Position;
	float4 Rotation;
	float3 Scale;
};

ConstantBuffer<ModelData> ModelDataBuffer : register(b1);

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

	// Object Space

	/* Scaling */

	float3 Position = (input.Position * ModelDataBuffer.Scale);

	Output.Normal = input.Normal;

	/* Rotation */

	Position = ((ModelDataBuffer.Rotation.xyz * (2.0f * dot(Position, ModelDataBuffer.Rotation.xyz))) + (Position * ((ModelDataBuffer.Rotation.w * ModelDataBuffer.Rotation.w) - dot(ModelDataBuffer.Rotation.xyz, ModelDataBuffer.Rotation.xyz))) + (cross(Position, ModelDataBuffer.Rotation.xyz) * (2.0f * ModelDataBuffer.Rotation.w)));

	Output.Normal = ((ModelDataBuffer.Rotation.xyz * (2.0f * dot(Output.Normal, ModelDataBuffer.Rotation.xyz))) + (Output.Normal * ((ModelDataBuffer.Rotation.w * ModelDataBuffer.Rotation.w) - dot(ModelDataBuffer.Rotation.xyz, ModelDataBuffer.Rotation.xyz))) + (cross(Output.Normal, ModelDataBuffer.Rotation.xyz) * (2.0f * ModelDataBuffer.Rotation.w)));

	//float3 Normal = ((ModelDataBuffer.Rotation.xyz * (2.0f * dot(input.Normal, ModelDataBuffer.Rotation.xyz))) + (input.Normal * ((ModelDataBuffer.Rotation.w * ModelDataBuffer.Rotation.w) - dot(ModelDataBuffer.Rotation.xyz, ModelDataBuffer.Rotation.xyz))) + (cross(input.Normal, ModelDataBuffer.Rotation.xyz) * (2.0f * ModelDataBuffer.Rotation.w)));

	/* Translation */

	Position = (Position + ModelDataBuffer.Position);

	Output.WorldSpacePosition = Position;

	// Camera Space

	/* Translation */

	float3 CameraDistance = (Position - CameraDataBuffer.Position);

	/* Rotation */

	Position = ((CameraDataBuffer.Rotation.xyz * (2.0f * dot(CameraDistance, CameraDataBuffer.Rotation.xyz))) + (CameraDistance * ((CameraDataBuffer.Rotation.w * CameraDataBuffer.Rotation.w) - dot(CameraDataBuffer.Rotation.xyz, CameraDataBuffer.Rotation.xyz))) + (cross(CameraDistance, CameraDataBuffer.Rotation.xyz) * (2.0f * CameraDataBuffer.Rotation.w)));

	// Clip Space

	float x = (Position.x * CameraDataBuffer.PerspectiveProjectionData.x);
	float y = (Position.y * CameraDataBuffer.PerspectiveProjectionData.y);
	float z = ((Position.z * CameraDataBuffer.PerspectiveProjectionData.z) + (CameraDataBuffer.PerspectiveProjectionData.w * CameraDataBuffer.PerspectiveProjectionData.z));
	float w = Position.z;

	Output.ScreenSpacePosition = float4(x, y, z, w);
	Output.TextureCoordinate   = input.TextureCoordinate;

	return Output;
}