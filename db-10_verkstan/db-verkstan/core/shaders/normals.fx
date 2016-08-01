float4x4 WorldViewProjection; 

struct VS_OUTPUT
{
    float4 Position  : POSITION;
    float3 Normal    : TEXCOORD1;
};

VS_OUTPUT vs(float4 position : POSITION, 
                        float3 normal : NORMAL)
{
	VS_OUTPUT output;
	output.Position = mul(position, WorldViewProjection);
	output.Normal = normal;
	return output;
}

float4 ps(VS_OUTPUT input) : COLOR0
{ 
 	return float4(input.Normal.x, input.Normal.y, input.Normal.z, 0.5f);
}

technique Normals
{
    	pass P0
    	{        
		VertexShader = compile vs_2_0 vs();  
        	PixelShader  = compile ps_2_0 ps();    
	}
}
