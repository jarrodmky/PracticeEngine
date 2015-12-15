//===========================================================================
// Filename:	Solid.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Solid.h"

using namespace Visualization;
using namespace Mathematics;

//===========================================================================
// Definitions
//===========================================================================

Solid::Solid(System& p_System)
	: Transform()
	, m_System(p_System)
	, m_TransformBuffer(p_System)
	, m_VertexBuffer(p_System)
	, m_IndexBuffer(p_System)
	, m_IndexCount(0)
{}

Solid::~Solid()
{}

void Solid::Initialize(const Mesh<ShadedVertex>& p_Mesh)
{
	Transform.Set();

	m_TransformBuffer.Allocate();

	//Vertex buffer
	m_VertexBuffer.Allocate(p_Mesh.GetVertices(), p_Mesh.GetVertexCount());

	//index buffer
	m_IndexBuffer.Allocate(p_Mesh.GetIndices(), p_Mesh.GetIndexCount(), p_Mesh.Topology);

	m_IndexCount = p_Mesh.GetIndexCount();
}

void Solid::Terminate()
{
	m_IndexBuffer.Free();
	m_VertexBuffer.Free();
	m_TransformBuffer.Free();
}

void Solid::Render(const Matrix44& p_ScalelessTransform)
{
	ObjectBuffer data;
	data.LocalToWorld = (p_ScalelessTransform * Transform.GetScaling()).Transposition();

	m_TransformBuffer.Set(&data);
	m_TransformBuffer.BindToVertexShader(3);
	
	m_VertexBuffer.Bind();
	m_IndexBuffer.Bind();

	m_System.GetContext()->DrawIndexed(m_IndexCount, 0, 0);
}