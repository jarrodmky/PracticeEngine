//====================================================================================================
// Filename:	DoSomething.fx
// Created by:	Jarrod MacKay
// Description: Shader that does something.
//====================================================================================================

struct VertexShaderInput
{
	float4 Position : POSITION;
	float4 Colour : COLOR;
};

struct VertexShaderOutput
{
	float4 Position : SV_POSITION;
	float4 Colour : COLOR;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VertexShaderOutput VS( VertexShaderInput vertex )
{
	VertexShaderOutput output;
	
	output.Position = vertex.Position;
	output.Colour = vertex.Colour;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS( VertexShaderOutput input) : SV_Target
{
	return input.Colour;
}
