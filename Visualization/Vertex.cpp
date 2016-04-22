//===========================================================================
// Filename:	Vertices.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Vertex.h"

using namespace Mathematics;
using namespace Visualization;
using namespace ColourPallet;

//===========================================================================
// Class Definitions
//===========================================================================

BasicVertex::BasicVertex(const Mathematics::Vector3& p_Position)
	: Position(p_Position)
{}

FlatVertex::FlatVertex(const Mathematics::Vector4& p_AffinePosition, const LinearColour& p_Colour)
	: Position(p_AffinePosition)
	, Colour(p_Colour)
{}

FlatVertex::FlatVertex(const Mathematics::Vector3& p_Position, const LinearColour& p_Colour)
	: FlatVertex(MakeAffinePoint(p_Position), p_Colour)
{}

LitVertex::LitVertex(
	const Mathematics::Vector3& p_Position,
	const Mathematics::LinearColour& p_Colour,
	const Mathematics::Vector3& p_Normal)
	: Position(p_Position)
	, Colour(p_Colour)
	, Normal(p_Normal)
{}

PaintedVertex::PaintedVertex(
	const Mathematics::Vector3& p_Position,
	const Mathematics::Vector2& p_TextureCoord)
	: Position(p_Position)
	, TextureCoord(p_TextureCoord)
{}

SurfaceVertex::SurfaceVertex(
	const Mathematics::Vector3& p_Position,
	const Mathematics::Vector3& p_Normal,
	const Mathematics::Vector2& p_TextureCoord)
	: Position(p_Position)
	, Normal(p_Normal)
	, TextureCoord(p_TextureCoord)
{}

FramedVertex::FramedVertex(
	const Mathematics::Vector3& p_Position,
	const Mathematics::Vector3& p_Normal,
	const Mathematics::Vector3& p_Tangent,
	const Mathematics::Vector2& p_TextureCoord)
	: Position(p_Position)
	, Normal(p_Normal)
	, Tangent(p_Tangent)
	, TextureCoord(p_TextureCoord)
{}