//--------------------------------------------------------------------------------------
// File: Tutorial04.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix viewProjection;
};

cbuffer MaterialBuffer : register(b1)
{
	vector materialAmbient;
	vector materialDiffuse;
	vector materialSpecular;
};

//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float3 position : POSITION;
	float3 normal : NORMAL;
};

//--------------------------------------------------------------------------------------

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.position = mul( float4(input.position.xyz, 1.0f), world );
	output.position = mul(output.position, viewProjection);
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return float4(materialDiffuse);
}
