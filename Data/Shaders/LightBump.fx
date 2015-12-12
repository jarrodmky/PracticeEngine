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
	matrix localToWorld;
}; 

cbuffer CameraBuffer : register(b1)
{
	float4 viewPosition;
	matrix worldToProjection;
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
Texture2D bumpMap : register(t1);
SamplerState mapState : register(s0);

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
    float2 texCoord : TEXCOORD;
};

//--------------------------------------------------------------------------------------

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
    float3 dirToLight : TEXCOORD1;
    float3 dirToView : TEXCOORD2;
    float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
	float4 posWorld = mul(float4(input.position, 1.0f), localToWorld);
	output.position = mul(posWorld, worldToProjection);
	
	output.texCoord = input.texCoord;
	output.dirToLight = normalize(-lightDirection.xyz);
	output.dirToView = normalize(viewPosition.xyz - posWorld.xyz);

	//frame
	output.normal = normalize(mul(input.normal, (float3x3)localToWorld));
	output.tangent = normalize(mul(input.tangent, (float3x3)localToWorld));
	output.binormal = normalize(mul(input.binormal, (float3x3)localToWorld));

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
	float3 normal = normalize(input.normal);
	float3 tangent = normalize(input.tangent);
	float3 binormal = normalize(input.binormal);
	float3 dirLight = normalize(input.dirToLight);
	float3 dirView = normalize(input.dirToView);
	float3 reflected = reflect(-dirLight, normal);

	float4 textureColour = diffuseMap.Sample(mapState, input.texCoord);
	float3 bumpColour = bumpMap.Sample(mapState, input.texCoord).xyz * 2.0f - 1.0f;

	float3 bumpNormal = normalize((bumpColour.x * input.tangent) + (bumpColour.y * input.normal) + (bumpColour.z * input.binormal));

	//ambience
	float4 ambient = lightAmbient * materialAmbient;

	//diffusion // TODO : USE BUMP NORMAL!!
	float d = saturate(dot(dirLight, normal));
	float4 diffuse = d * lightDiffuse * materialDiffuse;

	//specularity
	float s = (d > 0.0f) 
		? pow(saturate(dot(reflected, dirView)), materialReflectance) 
		: 0.0f;
	float4 specular = s * lightSpecular * materialSpecular;

	//texturing
	float4 diffuseColour = textureColour * saturate(ambient + diffuse);

	return saturate(diffuseColour + specular);
}
