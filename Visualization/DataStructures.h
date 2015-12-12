#ifndef IncludedVisuDataStructsH
#define IncludedVisuDataStructsH

//===========================================================================
// Filename:	DataStructs.h
// Author:		Jarrod MacKay
// Description:	Contains the necessary data structs for copying to the
//				constant buffers.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "System.h"

namespace Visualization
{
//===========================================================================
// Enumerations
//===========================================================================

	enum IndexTopology
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip
	};

//===========================================================================
// Structures
//===========================================================================

	struct ObjectBuffer
	{
		Mathematics::Matrix44 LocalToWorld;
	};

	struct CameraBuffer
	{
		Mathematics::Vector4 ViewPosition;
		Mathematics::Matrix44 WorldToViewToProjection;
	};

	struct TextureBuffer
	{
		u32 TextureHeight;
		u32 TextureWidth;
		Mathematics::LinearColour TextureAlpha;
	};

	struct MaterialBuffer
	{
		Mathematics::LinearColour MaterialEmissive;
		Mathematics::LinearColour MaterialAmbient;
		Mathematics::LinearColour MaterialDiffuse;
		Mathematics::LinearColour MaterialSpecular;
		f32 MaterialReflectance;
		f32 pad_a;
	};

	struct LightingBuffer
	{
		Mathematics::Vector4 LightDirection;
		Mathematics::LinearColour LightAmbient;
		Mathematics::LinearColour LightDiffuse;
		Mathematics::LinearColour LightSpecular;
	};
}

#endif // #ifndef IncludedVisuDataStructsH