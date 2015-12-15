//===========================================================================
// Filename:	BumpedSolid.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "BumpedSolid.h"

using namespace Visualization;
using namespace Mathematics;

//===========================================================================
// Definitions
//===========================================================================

BumpedSolid::BumpedSolid(System& p_System)
	: Transform()
	, m_System(p_System)
	, m_TransformBuffer(p_System)
	, m_VertexBuffer(p_System)
	, m_IndexBuffer(p_System)
	, m_IndexCount(0)
{}

BumpedSolid::~BumpedSolid()
{}

void BumpedSolid::Initialize(const Mesh<BumpedVertex>& p_Mesh)
{
	Transform.Set();

	m_TransformBuffer.Allocate();

	//Vertex buffer
	m_VertexBuffer.Allocate(p_Mesh.GetVertices(), p_Mesh.GetVertexCount());

	//index buffer
	m_IndexBuffer.Allocate(p_Mesh.GetIndices(), p_Mesh.GetIndexCount(), p_Mesh.Topology);

	m_IndexCount = p_Mesh.GetIndexCount();
}

void BumpedSolid::Terminate()
{
	m_IndexBuffer.Free();
	m_VertexBuffer.Free();
	m_TransformBuffer.Free();
}

void BumpedSolid::Render(const Matrix44& p_ScalelessTransform)
{
	ObjectBuffer data;
	data.LocalToWorld = (p_ScalelessTransform * Transform.GetScaling()).Transposition();

	m_TransformBuffer.Set(&data);
	m_TransformBuffer.BindToVertexShader(3);
	
	m_VertexBuffer.Bind();
	m_IndexBuffer.Bind();

	m_System.GetContext()->DrawIndexed(m_IndexCount, 0, 0);
}