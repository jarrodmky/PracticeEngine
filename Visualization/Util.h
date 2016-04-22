#ifndef INCLUDED_GRAPHICS_MESHUTIL_H
#define INCLUDED_GRAPHICS_MESHUTIL_H

//====================================================================================================
// Filename:	MeshUtil.h
// Created by:	Peter Chan
// Description:	Mesh related helper functions.
//====================================================================================================

#include "System.h"

//====================================================================================================
// Namespace
//====================================================================================================

namespace Visualization
{

namespace MeshUtil
{

using LayoutVector = std::vector<D3D11_INPUT_ELEMENT_DESC>;

//====================================================================================================
// Function Declarations
//====================================================================================================

void CreateVertexLayout(u32 vertexFormat, LayoutVector& layout);

} // namespace MeshUtil
} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_MESHUTIL_H