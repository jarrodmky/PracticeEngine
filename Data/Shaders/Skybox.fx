//--------------------------------------------------------------------------------------
// File: Skybox.fx
// By: Jarrod MacKay
// Uses a cubemap the render skybox geometry.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------------------------
cbuffer TransformBuffer : register( b0 )
{
	matrix WorldViewProjection;
};

TextureCube diffuseMap : register(t0);
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
    float3 texCoord : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    float4 output.position = mul( float4(input.position, 1.0f), WorldViewProjection );
	
	float3 normal = mul(float4(input.normal, 0.0f), world).xyz;
	normal = normalize(normal);

	float3 dirToLight = normalize(-lightDirection.xyz);
	float3 dirToView = normalize(viewPosition.xyz - output.position.xyz);

	output.normal = normal;
	output.dirToLight = dirToLight;
	output.dirToView = dirToView;
	output.texCoord = input.position.xyz;

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

	//ambience
	float4 ambient = lightAmbient * materialAmbient;

	//diffusion
	float d = saturate(dot(dirToLight, normal));
	float4 diffuse = d * lightDiffuse * materialDiffuse;

	//texturing
	float4 diffuseColour = diffuseMap.Sample(mapState, input.texCoord) * (ambient + diffuse);

	//specularity
	float ldn = dot(dirToLight, normal);
	float3 reflected = 2.0f * (normal * ldn) - dirToLight;
	float s = saturate(dot(reflected, dirToView));

	float4 specular = float4(0.0f, 0.0f, 0.0f, 1.0f);

	[flatten] if(ldn > 0.0f)
	{
		specular = s * lightSpecular * materialSpecular;
	}

	return diffuseColour + specular;
}
