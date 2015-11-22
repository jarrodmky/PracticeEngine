//--------------------------------------------------------------------------------------
// File: Lighting.fx
// By: Jarrod MacKay
// Basic flat shading
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------------------------
cbuffer TransformBuffer : register( b0 )
{
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer MaterialBuffer : register(b1)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
};

cbuffer LightingBuffer : register( b2 )
{
	float3 viewPosition;
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
};

Texture2D diffuseMap : register(t0);
SamplerState sampleTaker : register(s0);

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float3 position : POSITION;
	float3 normal : NORMAL;
    //float2 texCoord : TEXCOORD;
};

//--------------------------------------------------------------------------------------

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 normal : TEXCOORD0;
    float3 dirToLight : TEXCOORD1;
    float3 dirToView : TEXCOORD2;
    //float2 texCoord : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    float4 posWorld = mul( float4(input.position, 1.0f), world );
    output.position = mul( posWorld, view );
    output.position = mul( output.position, projection );
	
	float3 normal = mul(float4(input.normal, 0.0f), world).xyz;
	normal = normalize(normal);

	float3 dirToLight = normalize(-lightDirection);
	float3 dirToView = normalize(viewPosition - posWorld.xyz);

	output.normal = normal;
	output.dirToLight = dirToLight;
	output.dirToView = dirToView;
	//output.texCoord = input.texCoord;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
	float3 normal = normalize(input.normal);
	float3 dirToLight = normalize(input.dirToLight);
	float3 dirToView = normalize(input.dirToView);

	float4 ambient = lightAmbient * materialAmbient;

	float d = saturate(dot(dirToLight, normal));
	float4 diffuse = d * lightDiffuse * materialDiffuse;

	float3 r = reflect(-dirToLight, normal);
	float s = saturate(dot(r, dirToView));
	float4 specular = s * lightSpecular * materialSpecular;

	//float4 diffuseColour = diffuseMap.Sample(sampleTaker, input.texCoord);

	return (ambient + diffuse) /** diffuseColour + specular*/;
}
