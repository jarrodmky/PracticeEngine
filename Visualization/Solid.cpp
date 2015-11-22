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
	, m_Material()
	, m_TransformBuffer()
	, m_LightingBuffer()
	, m_MaterialBuffer()
	, m_VertexBuffer()
	, m_IndexBuffer()
	, m_VertexShader()
	, m_PixelShader()
	, m_IndexCount(0)
{}

Solid::~Solid()
{}

void Solid::Initialize(const Material& p_Material)
{
	m_Material = p_Material;
	m_TransformBuffer.Initialize(m_GraphicsSystem);
	m_LightingBuffer.Initialize(m_GraphicsSystem);
	m_MaterialBuffer.Initialize(m_GraphicsSystem);

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
	m_VertexBuffer.Free();
	
	m_MaterialBuffer.Terminate();
	m_LightingBuffer.Terminate();
	m_TransformBuffer.Terminate();
}

void Solid::Render(const TransformData& p_Transformations, const LightingData* p_Lighting) const
{
	ID3D11DeviceContext* context = m_GraphicsSystem.GetContext();

	m_VertexShader.Bind(context);
	m_PixelShader.Bind(context);

	m_TransformBuffer.Set(m_GraphicsSystem, p_Transformations);
	m_TransformBuffer.BindVS(m_GraphicsSystem, 0);

	MaterialData mat = { m_Material.Ambient
					   , m_Material.Diffuse
					   , m_Material.Specular};

	m_MaterialBuffer.Set(m_GraphicsSystem, mat);
	m_MaterialBuffer.BindPS(m_GraphicsSystem, 1);

	if(p_Lighting != nullptr)
	{
		m_LightingBuffer.Set(m_GraphicsSystem, *p_Lighting);
		m_LightingBuffer.BindVS(m_GraphicsSystem, 2);
		m_LightingBuffer.BindPS(m_GraphicsSystem, 2);
	}
	
	m_VertexBuffer.Bind(context);
	m_IndexBuffer.Bind(context);

	context->DrawIndexed(m_IndexCount, 0, 0);
}