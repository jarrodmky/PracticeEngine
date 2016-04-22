#ifndef IncludedVisuCommonH
#define IncludedVisuCommonH

//===========================================================================
// Filename:	Common.h
// Author:		Jarrod MacKay
// Description:	Common headers and definitions for internal and external usage.
//===========================================================================

#define UseDirect3D

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Abstracts.h>
#include <Mathematics.h>
#include <Meta.h>
#include <Algorithms.h>
#include <Serialization.h>

#ifdef UseDirect3D

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#else

#include <GL/GL.h>
#include <gl/GLU.h>

#endif

//===========================================================================
// Macros
//===========================================================================

//===========================================================================
// Functions
//===========================================================================

#endif //#ifndef IncludedVisuCommonH