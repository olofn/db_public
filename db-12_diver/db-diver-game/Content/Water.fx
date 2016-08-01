
sampler samplerState;
uniform extern float time; 

float4 ripple2( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = float4(0,0,0,0);
    
    for(int x=-1; x<2; x++)
    {
		for(int y=-1; y<2; y++)
		{
			float2 offset = float2((x - 0.5f) / (512.0f * 3.5f), (y - 0.5f) / (512.0f * 3.5f));
			Color += tex2D(samplerState, Tex + offset + float2(sin(time + Tex.y * 30),sin(time + Tex.x * 30)) * 0.001);
		}
    }
        
    return Color / 9.0f;
}

/*
float4 ripple3( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = float4(0,0,0,0);
    
    for(int x=-2; x<5; x++)
    {
		for(int y=-2; y<5; y++)
		{
			float2 offset = float2(x / (512.0f * 3.0f), y / (512.0f * 3.0f));
			Color += tex2D(samplerState, Tex + offset + float2(sin(time + Tex.y * 30),sin(time + Tex.x * 30)) * 0.001);
		}
    }
        
    return Color / 9.0f;
}
*/
technique GreyScale 
{
    pass P0 
    {
		//PixelShader = compile ps_3_0 ripple3();
        PixelShader = compile ps_2_0 ripple2();        
    }
}

