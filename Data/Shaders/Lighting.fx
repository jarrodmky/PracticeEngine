//--------------------------------------------------------------------------------------
// File: Lighting.fx
// By: Jarrod MacKay
// Basic flat shading
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------------------------
//VERTEX SHADER BUFFERS
cbuffer ObjectBuffer : register( b0 )
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

cbuffer MaterialBuffer : register(b3)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
};

Texture2D diffuseMap : register(t0);
SamplerState mapState : register(s0);

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float3 position : POSITION;
	float3 normal : NORMAL;
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
	float4 posWorld = mul(float4(input.position, 1.0f), localToWorld);
	output.position = mul(posWorld, worldToProjection);
	
	float3 normal = mul(float4(input.normal, 0.0f), localToWorld).xyz;
	normal = normalize(normal);

	float3 dirToLight = normalize(-lightDirection.xyz);
	float3 dirToView = normalize(viewPosition.xyz - posWorld.xyz);

	output.normal = normal;
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
	float intensity = 3.0f;

	float3 normal = normalize(input.normal);
	float3 dirLight = normalize(input.dirToLight);
	float3 dirView = normalize(input.dirToView);

	//ambience
	float4 ambient = saturate(lightAmbient * materialAmbient);

	//diffusion
	float d = saturate(dot(dirLight, normal));
	float4 diffuse = d * saturate(lightDiffuse * materialDiffuse);

	//texturing
	float4 diffuseColour = diffuseMap.Sample(mapState, input.texCoord) * (ambient + diffuse);

	//specularity
	float ldn = dot(dirLight, normal);
	float3 reflected = 2.0f * (normal * ldn) - dirLight;
	float s = saturate(dot(reflected, dirView));

	float4 specular = float4(0.0f, 0.0f, 0.0f, 1.0f);

	[flatten] if(ldn > 0.0f)
	{
		specular = s * lightSpecular * materialSpecular;
	}

	return diffuseColour + specular;
}
