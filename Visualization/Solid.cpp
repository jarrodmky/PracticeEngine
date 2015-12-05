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
	, m_TransformBuffer()
	, m_VertexBuffer(p_System)
	, m_IndexBuffer(p_System)
	, m_IndexCount(0)
{}

Solid::~Solid()
{}

void Solid::Initialize(const Mesh<ShadedVertex>& p_Mesh)
{
	Transform.Set();

	m_TransformBuffer.Initialize(m_System);

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
	m_TransformBuffer.Terminate();
}

void Solid::Render() const
{
	ObjectBuffer data;
	data.LocalToWorld = Transform.LocalToWorld().Transposition();

	m_TransformBuffer.Set(m_System, data);
	m_TransformBuffer.BindVS(m_System, 0);
	
	m_VertexBuffer.Bind();
	m_IndexBuffer.Bind();

	m_System.GetContext()->DrawIndexed(m_IndexCount, 0, 0);
}