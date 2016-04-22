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
		Position = 0x1 << 0,
		HomogPosition = 0x1 << 1,
		Colour = 0x1 << 2,
		Textured = 0x1 << 3,
		Normal = 0x1 << 4,
		Tangent = 0x1 << 5
	};

	//===========================================================================
	// Classes
	//===========================================================================


	struct BasicVertex
	{
		//Attributes
		const static u32 Format = Position;

		Mathematics::Vector3 Position;

		//Operators
		BasicVertex(const Mathematics::Vector3& p_Position = Mathematics::Zero3());
	};

	struct FlatVertex
	{
		//Attributes
		const static u32 Format = HomogPosition | Colour;

		Mathematics::Vector4 Position;
		Mathematics::LinearColour Colour;

		//Operators
		explicit FlatVertex(const Mathematics::Vector3& p_Position = Mathematics::Zero3()
			, const Mathematics::LinearColour& p_Colour = Mathematics::ColourPallet::White);
		explicit FlatVertex(const Mathematics::Vector4& p_AffinePosition
			, const Mathematics::LinearColour& p_Colour = Mathematics::ColourPallet::White);
	};

	struct LitVertex
	{
		//Attributes
		const static u32 Format = Position | Colour | Normal;

		Mathematics::Vector3 Position;
		Mathematics::LinearColour Colour;
		Mathematics::Vector3 Normal;

		//Operators
		LitVertex(const Mathematics::Vector3& p_Position = Mathematics::Zero3()
			, const Mathematics::LinearColour& p_Colour = Mathematics::ColourPallet::White
			, const Mathematics::Vector3& p_Normal = Mathematics::Zero3());
	};

	struct PaintedVertex
	{
		//Attributes
		const static u32 Format = Position | Textured;

		Mathematics::Vector3 Position;
		Mathematics::Vector2 TextureCoord;

		//Operators
		PaintedVertex(const Mathematics::Vector3& p_Position = Mathematics::Zero3()
			, const Mathematics::Vector2& p_TextureCoord = Mathematics::Zero2());
	};

	struct SurfaceVertex
	{
		//Attributes
		const static u32 Format = Position | Normal | Textured;

		Mathematics::Vector3 Position;
		Mathematics::Vector3 Normal;
		Mathematics::Vector2 TextureCoord;

		//Operators
		SurfaceVertex(const Mathematics::Vector3& p_Position = Mathematics::Zero3()
			, const Mathematics::Vector3& p_Normal = Mathematics::Zero3()
			, const Mathematics::Vector2& p_TextureCoord = Mathematics::Zero2());
	};

	struct FramedVertex
	{
		//Attributes
		const static u32 Format = Position | Normal | Tangent | Textured;

		Mathematics::Vector3 Position;
		Mathematics::Vector3 Normal;
		Mathematics::Vector3 Tangent;
		Mathematics::Vector2 TextureCoord;

		//Operators
		FramedVertex(const Mathematics::Vector3& p_Position = Mathematics::Zero3()
			, const Mathematics::Vector3& p_Normal = Mathematics::Zero3()
			, const Mathematics::Vector3& p_Tangent = Mathematics::Zero3()
			, const Mathematics::Vector2& p_TextureCoord = Mathematics::Zero2());
	};

	//===========================================================================
	// Functions
	//===========================================================================

	inline bool HasPosition(const u32 p_Format)
	{
		return (p_Format & Position) != 0;
	}

	inline bool HasHomogeneousPosition(const u32 p_Format)
	{
		return (p_Format & HomogPosition) != 0;
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

	inline bool HasTexture(const u32 p_Format)
	{
		return (p_Format & Textured) != 0;
	}

}

#endif // #ifndef IncludedVisuVerticesH