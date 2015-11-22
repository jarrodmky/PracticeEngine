//====================================================================================================
// Filename:	MeshUtil.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "MeshUtil.h"

#include "Vertices.h"

using namespace Visualization;

//====================================================================================================
// Function Definitions
//====================================================================================================

void MeshUtil::CreateVertexLayout(u32 vertexFormat, std::vector<D3D11_INPUT_ELEMENT_DESC>& layout)
{
	layout.clear();
	u32 offset = 0;

	if (vertexFormat & VertexFormat::Position)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "POSITION";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 12;
	}
	if (vertexFormat & VertexFormat::Normal)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "NORMAL";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 12;
	}
	//if (vertexFormat & VertexFormat::Tangent)
	//{
	//	D3D11_INPUT_ELEMENT_DESC desc;
	//	desc.SemanticName = "TANGENT";
	//	desc.SemanticIndex = 0;
	//	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//	desc.InputSlot = 0;
	//	desc.AlignedByteOffset = offset;
	//	desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//	desc.InstanceDataStepRate = 0;
	//	layout.push_back(desc);
	//	offset += 12;
	//}
	if (vertexFormat & VertexFormat::Colour)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "COLOR";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 16;
	}
	if (vertexFormat & VertexFormat::Textured)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "TEXCOORD";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 8;
	}
}