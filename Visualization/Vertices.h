#ifndef IncludedVisuVerticesH
#define IncludedVisuVerticesH

//===========================================================================
// Filename:	Vertices.h
// Author:		Jarrod MacKay
// Description:	Define a number of useful vertex types
//===========================================================================
	
//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include "LinearColour.h"
#include "Common.h"

namespace Visualization
{
	
//===========================================================================
// Definitions
//===========================================================================

	enum VertexFormat
	{
		Position	= 0x1 << 0,
		Colour		= 0x1 << 1,
		Normal		= 0x1 << 2,
		Textured		= 0x1 << 3
	};

//===========================================================================
// Classes
//===========================================================================


	struct BasicVertex
	{
	//Attributes
		const static u32 Format = Position | Colour;

		const static D3D11_INPUT_ELEMENT_DESC Layout[2];

		const static UINT NumberOfComponents = 2;

		Mathematics::Vector Position;

		LinearColour Colour;

	//Operators
		BasicVertex();

		BasicVertex(const Mathematics::Vector& p_Position, const LinearColour& p_Colour);
	};

	struct SurfaceVertex
	{
		//Attributes
		const static u32 Format = Position | Colour | Normal;

		const static D3D11_INPUT_ELEMENT_DESC Layout[3];

		const static UINT NumberOfComponents = 3;

		Mathematics::Vector Position;

		Mathematics::Vector Normal;

		LinearColour Colour;

		//Operators
		SurfaceVertex();

		SurfaceVertex(const Mathematics::Vector& p_Position, const LinearColour& p_Colour, const Mathematics::Vector& p_Normal);
	};

	struct TexturedVertex
	{
		//Attributes
		const static u32 Format = Position | Normal | Textured;

		const static D3D11_INPUT_ELEMENT_DESC Layout[3];

		const static UINT NumberOfComponents = 3;

		Mathematics::Vector Position;

		Mathematics::Vector Normal;

		f32 U;

		f32 V;

		//Operators
		TexturedVertex();

		TexturedVertex(const Mathematics::Vector& p_Position, const Mathematics::Vector& p_Normal, const Mathematics::scalarPair& p_Coords);
	};

//===========================================================================
// Functions
//===========================================================================

	inline bool HasPosition(const u32 p_Format)
	{
		return (p_Format & Position) != 0;
	}
	
	inline bool HasColour(const u32 p_Format)
	{
		return (p_Format & Colour) != 0;
	}

	inline bool HasNormal(const u32 p_Format)
	{
		return (p_Format & Normal) != 0;
	}

	inline bool HasTexture(const u32 p_Format)
	{
		return (p_Format & Textured) != 0;
	}

}

#endif // #ifndef IncludedVisuVerticesH