//===========================================================================
// Filename:	Precompiled.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Solid.h"

using namespace Visualization;

//===========================================================================
// Definitions
//===========================================================================

Solid::Solid(System& p_GraphicsSystem)
	: Mesh()
	, m_GraphicsSystem(p_GraphicsSystem)
	, m_TransformBuffer()
	, m_VertexBuffer()
	, m_IndexBuffer()
	, m_VertexShader()
	, m_PixelShader()
	, m_IndexCount(0)
{}

Solid::~Solid()
{}

void Solid::Initialize()
{
	m_TransformBuffer.Initialize(m_GraphicsSystem);

	//Vertex buffer
	m_VertexBuffer.Allocate(Mesh.GetVertices(), Mesh.GetVertexCount(), m_GraphicsSystem.GetDevice());

	//index buffer
	m_IndexBuffer.Allocate(Mesh.GetIndices(), Mesh.GetIndexCount(),  m_GraphicsSystem.GetDevice(), Mesh.Topology);

	//vertex shader compile
	m_VertexShader.Compile(L"../Data/Shaders/Lighting.fx", m_GraphicsSystem.GetDevice());

	//pixel shader compile
	m_PixelShader.Compile(L"../Data/Shaders/Lighting.fx", m_GraphicsSystem.GetDevice());

	m_IndexCount = Mesh.GetIndexCount();
	Mesh.Destroy();
}

void Solid::Terminate()
{
	m_PixelShader.Release();
	m_VertexShader.Release();
	m_IndexBuffer.Free();
	m_VertexBuffer.Free();;

	m_TransformBuffer.Terminate();
}

void Solid::Render(const SceneData& p_Transformations) const
{
	ID3D11DeviceContext* context = m_GraphicsSystem.GetContext();

	m_VertexShader.Bind(context);
	m_PixelShader.Bind(context);

	m_TransformBuffer.Set(m_GraphicsSystem, p_Transformations);
	m_TransformBuffer.BindVS(m_GraphicsSystem, 0);
	m_VertexBuffer.Bind(context);
	m_IndexBuffer.Bind(context);

	context->DrawIndexed(m_IndexCount, 0, 0);
}