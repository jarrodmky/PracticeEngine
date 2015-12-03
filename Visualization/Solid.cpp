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

Solid::Solid(System& p_System)
	: Transform()
	, m_System(p_System)
	, m_Material()
	, m_TransformBuffer()
	, m_LightingBuffer()
	, m_MaterialBuffer()
	, m_VertexBuffer(p_System)
	, m_IndexBuffer(p_System)
	, m_VertexShader(p_System)
	, m_PixelShader(p_System)
	, m_IndexCount(0)
{}

Solid::~Solid()
{}

void Solid::Initialize(const Material& p_Material, const Mesh<ShadedVertex>& p_Mesh)
{
	m_Material = p_Material;
	m_TransformBuffer.Initialize(m_System);
	m_LightingBuffer.Initialize(m_System);
	m_MaterialBuffer.Initialize(m_System);

	//Vertex buffer
	m_VertexBuffer.Allocate(p_Mesh.GetVertices(), p_Mesh.GetVertexCount());

	//index buffer
	m_IndexBuffer.Allocate(p_Mesh.GetIndices(), p_Mesh.GetIndexCount(), p_Mesh.Topology);

	//vertex shader compile
	m_VertexShader.Compile(L"../Data/Shaders/Lighting.fx", "VS", "vs_4_0");

	//pixel shader compile
	m_PixelShader.Compile(L"../Data/Shaders/Lighting.fx", "PS", "ps_4_0");

	m_IndexCount = p_Mesh.GetIndexCount();

	Transform.Set();
}

void Solid::Terminate()
{
	m_PixelShader.Release();
	m_VertexShader.Release();
	m_IndexBuffer.Free();
	m_VertexBuffer.Free();
	
	m_MaterialBuffer.Terminate();
	m_LightingBuffer.Terminate();
	m_TransformBuffer.Terminate();
}

void Solid::Render(const TransformBuffer& p_Transformations, const LightingBuffer* p_Lighting) const
{
	m_VertexShader.Bind();
	m_PixelShader.Bind();

	m_TransformBuffer.Set(m_System, p_Transformations);
	m_TransformBuffer.BindVS(m_System, 0);

	MaterialBuffer mat = { m_Material.Ambient
					   , m_Material.Diffuse
					   , m_Material.Specular};

	m_MaterialBuffer.Set(m_System, mat);
	m_MaterialBuffer.BindPS(m_System, 1);

	if(p_Lighting != nullptr)
	{
		m_LightingBuffer.Set(m_System, *p_Lighting);
		m_LightingBuffer.BindVS(m_System, 2);
		m_LightingBuffer.BindPS(m_System, 2);
	}
	
	m_VertexBuffer.Bind();
	m_IndexBuffer.Bind();

	m_System.GetContext()->DrawIndexed(m_IndexCount, 0, 0);
}