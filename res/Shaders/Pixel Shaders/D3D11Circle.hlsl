struct PSInput
{
	float4 Position          : SV_POSITION;
	float4 Color             : COLOR;
	float2 TextureCoordinate : TEXTURECOORDINATE;
};

float4 main(PSInput input) : SV_TARGET
{
	float TextureCoordinateX = ((2 * input.TextureCoordinate.x) - 1);
	float TextureCoordinateY = ((2 * input.TextureCoordinate.y) - 1);

	float Distance = ((TextureCoordinateX * TextureCoordinateX) + (TextureCoordinateY * TextureCoordinateY));
    
	if (Distance < 1)
	{
		return float4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		return float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}