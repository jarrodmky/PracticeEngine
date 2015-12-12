//--------------------------------------------------------------------------------------
// File: Lighting.fx
// By: Jarrod MacKay
// Basic flat shading
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------------------------
//VERTEX SHADER BUFFERS
cbuffer ObjectBuffer : register( b3 )
{
	float4x4 localToWorld;
}; 

cbuffer CameraBuffer : register(b1)
{
	float4 viewPosition;
	float4x4 worldToProjection;
};

//VETEX AND PIXEL SHADER BUFFERS

cbuffer LightingBuffer : register( b2)
{
	float4 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
};

//PIXEL SHADER BUFFERS

cbuffer MaterialBuffer : register(b0)
{
	float4 materialEmissive;
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float materialReflectance;
};

Texture2D diffuseMap : register(t0);
SamplerState mapState : register(s0);

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float4 position : POSITION;
	float4 normal : NORMAL;
    float2 texCoord : TEXCOORD;
};

//--------------------------------------------------------------------------------------

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 normal : TEXCOORD0;
    float3 dirToLight : TEXCOORD1;
    float3 dirToView : TEXCOORD2;
    float2 texCoord : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
	float4 posWorld = mul(input.position, localToWorld);
	output.position = mul(posWorld, worldToProjection);
	
	float4 normal = mul(input.normal, localToWorld);
	normal = normalize(normal);

	float3 dirToLight = normalize(-lightDirection.xyz);
	float3 dirToView = normalize(viewPosition.xyz - posWorld.xyz);

	output.normal = normal.xyz;
	output.dirToLight = dirToLight;
	output.dirToView = dirToView;
	output.texCoord = input.texCoord;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
	float3 normal = normalize(input.normal);
	float3 dirLight = normalize(input.dirToLight);
	float3 dirView = normalize(input.dirToView);
	float3 reflected = reflect(-dirLight, normal);

	//ambience
	float4 ambient = lightAmbient * materialAmbient;

	//diffusion
	float d = saturate(dot(dirLight, normal));
	float4 diffuse = d * lightDiffuse * materialDiffuse;

	//texturing
	float4 diffuseColour = diffuseMap.Sample(mapState, input.texCoord) * saturate(ambient + diffuse);

	//specularity
	float s = (d > 0.0f) 
		? pow(saturate(dot(reflected, dirView)), materialReflectance) 
		: 0.0f;
	float4 specular = s * lightSpecular * materialSpecular;

	return saturate(diffuseColour + specular);
}
