//--------------------------------------------------------------------------------------
// File: ParticleBillboard.fx
// By: Jarrod MacKay
// Computes a billboard quad and renders a texture to it based only on a location.
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

//GEOMETRY AND PIXEL SHADER
cbuffer BillboardBuffer
{
	float4 upVector;
	float4 diffuseColour;
	float textureHeight;
	float textureWidth;
};

Texture2D bbMap : register(t0);
SamplerState mapState : register(s0);

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float4 position : POSITION;
};

//--------------------------------------------------------------------------------------

struct VS_OUTPUT
{
	float4 position : POSITION;
	float4 up : TEXCOORD;
};

//--------------------------------------------------------------------------------------

struct GS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(in VS_INPUT input )
{
	//change to perspective space
    VS_OUTPUT output = (VS_OUTPUT)0;
	//output.position = mul(mul(input.position, localToWorld), worldToProjection);
	output.position = mul(mul(input.position, localToWorld), worldToProjection);
    return output;
}

//--------------------------------------------------------------------------------------
// Geometry Shader
//--------------------------------------------------------------------------------------
[maxvertexcount(6)]
void GS(point VS_OUTPUT input[1], inout TriangleStream<GS_OUTPUT> outputStream)
{
	const float4 p = input[0].position;
	const float h = textureHeight * 0.5f;
	const float w = textureWidth * 0.5f;

	GS_OUTPUT v[4];

	v[0].position = p + float4(-w, h, 0.0f, 0.0f);
	v[0].texCoord = float2(0.0f, 0.0f);

	v[1].position = p + float4(w, h, 0.0f, 0.0f);
	v[1].texCoord = float2(1.0f, 0.0f);

	v[2].position = p + float4(-w, -h, 0.0f, 0.0f);
	v[2].texCoord = float2(0.0f, 1.0f);

	v[3].position = p + float4(w, -h, 0.0f, 0.0f);
	v[3].texCoord = float2(1.0f, 1.0f);

	outputStream.Append(v[0]);
	outputStream.Append(v[1]);
	outputStream.Append(v[2]);

	//outputStream.RestartStrip();

	outputStream.Append(v[2]);
	outputStream.Append(v[3]);
	outputStream.Append(v[1]);

	outputStream.RestartStrip();
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(in GS_OUTPUT input ) : SV_Target
{	
	return diffuseColour;//bbMap.Sample(mapState, input.texCoord);
}
