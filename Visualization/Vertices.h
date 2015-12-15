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
		Textured	= 0x1 << 2,
		Normal		= 0x1 << 3,
		Tangent     = 0x1 << 4,
		Binormal    = 0x1 << 5
	};

//===========================================================================
// Classes
//===========================================================================


	struct EmptyVertex
	{
		//Attributes
		const static u32 Format = Position;

		Mathematics::Vector4 Position;

		//Operators
		EmptyVertex();

		EmptyVertex(const Mathematics::Vector3& p_Position);
	};

	struct FlatVertex
	{
	//Attributes
		const static u32 Format = Position | Colour;

		Mathematics::Vector4 Position;

		Mathematics::LinearColour Colour;

	//Operators
		FlatVertex();

		FlatVertex(const Mathematics::Vector3& p_Position, const Mathematics::LinearColour& p_Colour);
	};

	struct ShadedVertex
	{
		//Attributes
		const static u32 Format = Position | Normal | Textured;

		Mathematics::Vector4 Position;

		Mathematics::Vector4 Normal;

		Mathematics::Vector2 TextureCoord;

		//Operators
		ShadedVertex();

		ShadedVertex(const Mathematics::Vector3& p_Position
			, const Mathematics::Vector3& p_Normal
			, const Mathematics::Vector2& p_TextureCoord);
	};

	struct BumpedVertex
	{
		//Attributes
		const static u32 Format = Position | Normal | Tangent | Binormal | Textured;

		Mathematics::Vector4 Position;

		Mathematics::Vector4 Normal;

		Mathematics::Vector4 Tangent;

		Mathematics::Vector4 Binormal;

		Mathematics::Vector2 TextureCoord;

		//Operators
		BumpedVertex();

		BumpedVertex(const Mathematics::Vector3& p_Position
			, const Mathematics::Vector3& p_Normal
			, const Mathematics::Vector3& p_Tangent
			, const Mathematics::Vector2& p_TextureCoord);
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

	inline bool HasTangent(const u32 p_Format)
	{
		return (p_Format & Tangent) != 0;
	}

	inline bool HasNormal(const u32 p_Format)
	{
		return (p_Format & Normal) != 0;
	}

	inline bool HasBinormal(const u32 p_Format)
	{
		return (p_Format & Binormal) != 0;
	}

	inline bool HasTexture(const u32 p_Format)
	{
		return (p_Format & Textured) != 0;
	}

}

#endif // #ifndef IncludedVisuVerticesH