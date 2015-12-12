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
	output.position = mul(mul(input.position, localToWorld), worldToProjection);
    return output;
}

//--------------------------------------------------------------------------------------
// Geometry Shader
//--------------------------------------------------------------------------------------
void GS(point VS_OUTPUT input, inout TriangleStream<GS_OUTPUT> outputStream)
{
	const float4 p = input.position;
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

	output.Append(v[0]);
	output.Append(v[1]);
	output.Append(v[2]);

	output.RestartStrip();

	output.Append(v[0]);
	output.Append(v[2]);
	output.Append(v[3]);

	output.RestartStrip();
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(in GS_OUTPUT input ) : SV_Target
{	
	return float4(1.0f, 1.0f, 1.0f, 1.0f);//bbMap.Sample(mapState, input.texCoord);
}
