float4x4 matViewProjection;
float4x4 matWorld;

sampler2D diffuseTex;

struct GeometryVSInput 
{
   float4 position : POSITION;
   float3 normal : NORMAL;
   float2 uv : TEXCOORD0;
};

struct GeometryVSOutput 
{
   float4 position : POSITION;
   float3 positionPass : TEXCOORD0;
   float3 normal : TEXCOORD1;
   float2 uv : TEXCOORD2;
   float depth : TEXCOORD3;
};

GeometryVSOutput vs_geometry(GeometryVSInput input)
{
   GeometryVSOutput output;
   output.position = mul(input.position, matViewProjection);
   output.positionPass = input.position.xyz;
   output.depth = output.position.z;
   output.normal = input.normal;
   output.uv = input.uv;
   return output;
}

struct GeometryPSInput
{
   float3 position : TEXCOORD0;
   float3 normal : TEXCOORD1;
   float2 uv : TEXCOORD2;
   float depth : TEXCOORD3;
};

struct GeometryPSOutput 
{
   float4 litPixels : COLOR0;
   float4 normalsDepth : COLOR1;
   float4 diffuseSpecular : COLOR2;
   float4 posRoughness : COLOR3;
};

GeometryPSOutput ps_geometry(GeometryPSInput input)
{
   float3 diffuse = tex2D(diffuseTex, input.uv).rgb;
   float spec = tex2D(diffuseTex, input.uv).a;

   GeometryPSOutput output;
   output.litPixels = float4(0.0f, 0.0f, 0.0f, 1.0f);
   output.normalsDepth = float4(input.normal, input.depth);
   output.diffuseSpecular = float4(diffuse, spec);
   output.posRoughness = float4(input.position, 1.0f);
   return output;
}

technique Deferred
{
	pass P0
	{
		VertexShader = compile vs_2_0 vs_geometry();
		PixelShader  = compile ps_2_0 ps_geometry();
	}
}

