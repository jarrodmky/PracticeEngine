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
using namespace ColourPallet;

//===========================================================================
// Class Definitions
//===========================================================================

FlatVertex::FlatVertex()
: Position(Zero)
, Colour(White)
{}

FlatVertex::FlatVertex(const Mathematics::Vector3& p_Position, const LinearColour& p_Colour)
: Position(MakePoint(p_Position))
, Colour(p_Colour)
{}

ShadedVertex::ShadedVertex()
	: Position(Zero)
	, Normal(X())
	, TextureCoord(Zero2())
{}

ShadedVertex::ShadedVertex(
	const Mathematics::Vector3& p_Position,
	const Mathematics::Vector3& p_Normal,
	const Mathematics::Vector2& p_TextureCoord)
	: Position(MakePoint(p_Position))
	, Normal(MakeVector(p_Normal))
	, TextureCoord(p_TextureCoord)
{}

BumpedVertex::BumpedVertex()
	: Position(Zero)
	, Normal(X())
	, Tangent(Y())
	, Binormal(Z())
	, TextureCoord(Zero2())
{}

BumpedVertex::BumpedVertex(
	const Mathematics::Vector3& p_Position,
	const Mathematics::Vector3& p_Normal,
	const Mathematics::Vector3& p_Tangent,
	const Mathematics::Vector2& p_TextureCoord)
	: Position(MakePoint(p_Position))
	, Normal(MakeVector(p_Normal))
	, Tangent(MakeVector(p_Tangent))
	, Binormal(MakeVector(p_Tangent * p_Normal))
	, TextureCoord(p_TextureCoord)
{}