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
{}

ShadedVertex::ShadedVertex(
	const Mathematics::Vector& p_Position,
	const Mathematics::Vector& p_Normal)
	: Position(p_Position)
	, Normal(p_Normal)
{}

TexturedVertex::TexturedVertex()
	: Position(Zero)
	, Normal(I)
	, U(0.0f)
	, V(0.0f)
{}

TexturedVertex::TexturedVertex(const Mathematics::Vector& p_Position
							 , const Mathematics::Vector& p_Normal
							 , const scalarPair& p_Coords)
	: Position(p_Position)
	, Normal(p_Normal)
	, U(p_Coords.first)
	, V(p_Coords.second)
{}