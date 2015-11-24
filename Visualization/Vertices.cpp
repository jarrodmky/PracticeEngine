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

FlatVertex::FlatVertex()
: Position(Zero)
, Colour(White)
{}

FlatVertex::FlatVertex(const Mathematics::Vector& p_Position, const LinearColour& p_Colour)
: Position(p_Position)
, Colour(p_Colour)
{}

ShadedVertex::ShadedVertex()
	: Position(Zero)
	, Normal(I)
{
	UV[0] = 0.0f;
	UV[1] = 0.0f;
}

ShadedVertex::ShadedVertex(
	const Mathematics::Vector& p_Position,
	const Mathematics::Vector& p_Normal
	, const f32 p_U, const f32 p_V)
	: Position(p_Position)
	, Normal(p_Normal)
{
	UV[0] = p_U;
	UV[1] = p_V;
}