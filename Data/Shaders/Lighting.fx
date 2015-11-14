//--------------------------------------------------------------------------------------
// File: Lighting.fx
// By: Jarrod MacKay
// Basic flat shading
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix world;
	matrix view;
	matrix projection;
	vector viewPosition;
	vector lightDirection;
	vector lightAmbient;
	vector lightDiffuse;
	vector lightSpecular;
	vector materialAmbient;
	vector materialDiffuse;
	vector materialSpecular;
}

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float4 position : POSITION;
	float4 normal : NORMAL;
    float4 texCoord : TEXCOORD;
};

//--------------------------------------------------------------------------------------

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 normal : TEXCOORD0;
    float4 dirToLight : TEXCOORD1;
    float4 dirToView : TEXCOORD2;
    float4 texCoord : TEXCOORD3;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT)0;

	float4 posWorld = mul(input.Position, World);
    float4 posView = mul( PosWorld, View );
    float4 posProj = mul( PosView, Projection );
	
	float4 normal = mul(float4(input.Normal, 0.0f), World).xyz;
	normal = normalize(normal);

	float3 DirToLight = -normalize(LightDirection.xyz);
	float3 DirToView = normalize(ViewPosition.xyz - PosWorld.xyz);


    output.Position = PosProj;
	output.Normal = normal;
	output.DirToLight = DirToLight;
	output.DirToView = DirToView;
	output.TexCoord = TexCoord;

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

	float4 r = reflect(-dirToLight, normal);
	float s = saturate(dot(r, dirToView));
	float4 specular = s * lightSpecular * materialSpecular;

	return ambient + diffuse + specular;
}
