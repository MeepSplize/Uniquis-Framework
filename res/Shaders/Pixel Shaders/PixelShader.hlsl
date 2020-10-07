Texture2D Texture    : register(t0);
SamplerState Sampler : register(s0);

struct OpacityData
{
	float1 Opacity;
};

struct ColorData
{
	float3 Color;
};

struct AmbientLightData
{
	float1 Intensity;
};

struct DirectionalLightData
{
	float3 Color;
	float3 Direction;
	float1 Intensity;
};

//ConstantBuffer<DirectionalLightData> DirectionalLightDataBuffer : register(b0);

struct PointLightData
{
	float3 Color;
	float3 Position;
	float1 Intensity;
};

ConstantBuffer<PointLightData> PointLightDataBuffer : register(b0);

struct SpotLightData
{
	float3 Color;
	float3 Direction;
	float3 Position;
	float1 Intensity;
};

struct PSInput
{
	float3 WorldSpacePosition  : POSITION;
	float4 ScreenSpacePosition : SV_POSITION;
	float3 Normal              : NORMAL;
	float2 TextureCoordinate   : TEXTURECOORDINATE;
};

float4 main(PSInput input) : SV_TARGET
{
	float3 PixelColor = float3(0.0f, 0.0f, 0.0f);

	// Point Light

	float3 Direction = (input.WorldSpacePosition - PointLightDataBuffer.Position);

	float3 Distance = length(Direction);

	Direction /= Distance;

	float3 LightIntensity = -(dot(Direction, input.Normal));

	PixelColor += ((LightIntensity * PointLightDataBuffer.Color) / (0.25f * Distance));

	PixelColor = saturate(PixelColor + 0.25);

	//

	//return (float4(PixelColor, 1.0) * Texture.Sample(Sampler, input.TextureCoordinate));
	return Texture.Sample(Sampler, input.TextureCoordinate);
	//return (float4(DirectionalLightDataBuffer.ColorIntensity.xyz, 1.0f) * saturate(-(dot((input.Normal), DirectionalLightDataBuffer.Direction))));
}