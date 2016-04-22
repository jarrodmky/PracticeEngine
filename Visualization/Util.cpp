//====================================================================================================
// Filename:	MeshUtil.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Util.h"

#include "Vertex.h"

using namespace Visualization;

namespace
{
	enum LayoutElementType
	{
		TwoFloat = 8,
		ThreeFloat = 12,
		FourFloat = 16
	};

	void AddToLayout(MeshUtil::LayoutVector& layout, u32& offset, LayoutElementType type, const char* name)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = name;
		desc.SemanticIndex = 0;
		switch (type)
		{
		case TwoFloat:
			desc.Format = DXGI_FORMAT_R32G32_FLOAT;
			break;
		case ThreeFloat:
			desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case FourFloat:
			desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		default:
			Halt("Type has no format!");
			break;
		}			
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += type;
	}
}

//====================================================================================================
// Function Definitions
//====================================================================================================

void MeshUtil::CreateVertexLayout(u32 vertexFormat, LayoutVector& layout)
{
	layout.clear();
	u32 cumulativeOffset = 0;

	if (HasPosition(vertexFormat))
	{
		AddToLayout(layout, cumulativeOffset, ThreeFloat, "POSITION");
	}
	if (HasHomogeneousPosition(vertexFormat))
	{
		AddToLayout(layout, cumulativeOffset, FourFloat, "POSITION");
	}
	if (HasColour(vertexFormat))
	{
		AddToLayout(layout, cumulativeOffset, FourFloat, "COLOR");
	}
	if (HasNormal(vertexFormat))
	{
		AddToLayout(layout, cumulativeOffset, ThreeFloat, "NORMAL");
	}
	if (HasTangent(vertexFormat))
	{
		AddToLayout(layout, cumulativeOffset, ThreeFloat, "TANGENT");
	}
	if (HasTexture(vertexFormat))
	{
		AddToLayout(layout, cumulativeOffset, TwoFloat, "TEXCOORD");
	}
}