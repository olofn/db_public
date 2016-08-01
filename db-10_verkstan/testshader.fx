
sampler samplerState;

float4 testshader( float2 Tex : TEXCOORD0 ) : COLOR0
{
    return float4(1,0,0,0);
}

technique GreyScale 
{
    pass P0 
    {
	PixelShader = compile ps_2_0 testshader();        
    }
}

