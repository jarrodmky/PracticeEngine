//===========================================================================
// Filename:	Vertices.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Vertices.h"

using namespace Mathematics;
using namespace Visualization;
using namespace ConstantVectors;
using namespace ConstantColours;

//===========================================================================
// Class Definitions
//===========================================================================

BasicVertex::BasicVertex()
: Position(Null)
, Colour(White)
{}

BasicVertex::BasicVertex(const Mathematics::Vector& p_Position, const LinearColour& p_Colour)
: Position(p_Position)
, Colour(p_Colour)
{}

const D3D11_INPUT_ELEMENT_DESC BasicVertex::Layout[2] = 
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 } 
	, {"COLOR" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

SurfaceVertex::SurfaceVertex()
	: Position(Null)
	, Normal(I)
	, Colour(White)
{}

SurfaceVertex::SurfaceVertex(
	const Mathematics::Vector& p_Position, 
	const LinearColour& p_Colour, 
	const Mathematics::Vector& p_Normal)
	: Position(p_Position)
	, Normal(p_Normal)
	, Colour(p_Colour)
{}

const D3D11_INPUT_ELEMENT_DESC SurfaceVertex::Layout[3] = 
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	, {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	, {"COLOR" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
};