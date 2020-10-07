struct GSInput
{
	float4 Position          : SV_POSITION;
	float3 Normal            : NORMAL;
	float2 TextureCoordinate : TEXTURECOORDINATE;
};

struct GSOutput
{
	float4 Position          : SV_POSITION;
	float3 Normal            : NORMAL;
	float2 TextureCoordinate : TEXTURECOORDINATE;
};

[maxvertexcount(3)]
void main(triangle GSInput input[3], inout TriangleStream<GSOutput> OutputStream)
{
	GSOutput Output;

	//[unroll(3)]
    //for (uint i = 0; i < 3; i++)
    //{
    //    Output.Position          = input[i].Position;
    //    Output.Color             = input[i].Color;
    //    Output.TextureCoordinate = input[i].TextureCoordinate;
	//
    //    OutputStream.Append(Output);
    //}
	//
	//Output.Position          = input[0].Position;
    //Output.Color             = input[0].Color;
    //Output.TextureCoordinate = input[0].TextureCoordinate;
	//
    //OutputStream.Append(Output);

	for (uint i = 0; i < 3; i++)
	{
		Output.Position          = input[i].Position;
		Output.TextureCoordinate = input[i].TextureCoordinate;
	
		Output.Normal = cross((input[1].Position - input[0].Position), (input[2].Position - input[0].Position));
		 
		OutputStream.Append(Output);
	}
}