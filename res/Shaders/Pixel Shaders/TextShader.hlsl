Texture2D Texture    : register(t0);
SamplerState Sampler : register(s0);

struct PSInput
{
	float3 WorldSpacePosition  : POSITION;
	float4 ScreenSpacePosition : SV_POSITION;
	float3 Normal              : NORMAL;
	float2 TextureCoordinate   : TEXTURECOORDINATE;
};

float4 main(PSInput input) : SV_TARGET
{
	float4 Color = Texture.Sample(Sampler, input.TextureCoordinate);

	return Color * float4(1.0f, 0.0f, 0.0f, 1.0f);
}