//===========================================================================
// Filename:	LitRenderer.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Renderer.h"
#include "MeshBuilder.h"

using namespace Mathematics;
using namespace Visualization;

//===========================================================================
// Definitions
//===========================================================================

Renderer<LitVertex>::Renderer(System& p_System)
	: m_VertexShader(p_System)
	, m_PixelShader(p_System)
	, m_CameraBuffer(p_System)
	, m_LightBuffer(p_System)
	, m_ObjectBuffer(p_System)
	, m_Sphere(p_System)
	, m_Initialized(false)
	, m_Rendering(false)
	, m_System(p_System)
{}

Renderer<LitVertex>::~Renderer() 
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(!m_Initialized, "Still initialized!");
}

void Renderer<LitVertex>::Initialize()
{
	m_VertexShader.Compile();
	m_PixelShader.Compile();

	m_CameraBuffer.Allocate();
	m_ObjectBuffer.Allocate();
	m_LightBuffer.Allocate();

	Mesh<LitVertex> litMesh;
	MeshBuilder::CreateUnitSphere(litMesh, 4, ColourPallet::White);
	m_Sphere.Initialize(litMesh);
	litMesh.Destroy();

	m_Initialized = true;
}

void Renderer<LitVertex>::Terminate()
{
	m_LightBuffer.Free();
	m_ObjectBuffer.Free();
	m_CameraBuffer.Free();

	m_PixelShader.Release();
	m_VertexShader.Release();

	m_Sphere.Terminate();

	m_Initialized = false;
}

void Renderer<LitVertex>::RegisterLight(const Light& p_Light)
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(m_Initialized, "Not initialized!");

	m_LightBuffer.Data.LightColour = p_Light.Diffuse;
	m_LightBuffer.Data.LightWorldDirection = p_Light.Position;
	m_LightBuffer.Data.WorldAmbient = p_Light.Ambient;

	m_LightBuffer.Update();
}

void Renderer<LitVertex>::StartRendering(const Camera& p_Camera)
{
	Assert(!m_Rendering, "Already rendering!");
	Assert(m_Initialized, "Not initialized!");

	m_CameraBuffer.Data.WorldPosition = MakeAffinePoint(p_Camera.Transform.GetPosition());
	m_CameraBuffer.Data.WorldToProjection = p_Camera.GetWorldToPerspectiveTransform(static_cast<f32>(m_System.GetAspectRatio())).Transposition();

	m_CameraBuffer.Update();

	m_CameraBuffer.BindToVertexShader(0);

	m_LightBuffer.BindToVertexShader(2);
	m_LightBuffer.BindToPixelShader(2);

	m_VertexShader.Bind();
	m_PixelShader.Bind();

	m_Rendering = true;
}

void Renderer<LitVertex>::RenderSphere(const Mathematics::Sphere3& p_Sphere)
{
	Mathematics::Matrix44 locToWorld = MakeTransformation(p_Sphere.Centre, p_Sphere.Radius);
	Mathematics::Matrix44 locToWorldTransp = locToWorld.Transposition();
	m_ObjectBuffer.Data.LocalToProjection = locToWorldTransp * m_CameraBuffer.Data.WorldToProjection;
	m_ObjectBuffer.Data.LocalToWorld = locToWorldTransp;
	m_ObjectBuffer.Data.WorldToLocalTranpose = locToWorld;

	m_ObjectBuffer.Update();
	
	m_ObjectBuffer.BindToVertexShader(1);
	m_ObjectBuffer.BindToPixelShader(1);

	m_Sphere.m_VertexBuffer.Bind();
	m_Sphere.m_IndexBuffer.Draw(m_Sphere.m_Topology);
}

void Renderer<LitVertex>::StopRendering()
{
	Assert(m_Rendering, "Not rendering!");
	Assert(m_Initialized, "Not initialized!");
	m_Rendering = false;
}