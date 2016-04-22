//===========================================================================
// Filename:	FlatRenderer.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Renderer.h"

using namespace Mathematics;
using namespace Visualization;

//===========================================================================
// Definitions
//===========================================================================

Renderer<FlatVertex>::Renderer(System& p_System)
	: m_VertexShader(p_System)
	, m_PixelShader(p_System)
	, m_CameraBuffer(p_System)
	, m_Initialized(false)
	, m_Rendering(false)
	, m_System(p_System)
{}

//---------------------------------------------------------------------------

Renderer<FlatVertex>::~Renderer()
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(!m_Initialized, "Still initialized!");
}

//---------------------------------------------------------------------------

void Renderer<FlatVertex>::Initialize()
{
	Assert(!m_Rendering, "Rendering!");
	m_VertexShader.Compile();
	m_PixelShader.Compile();
	m_CameraBuffer.Allocate(nullptr);
	m_Initialized = true;
}

//---------------------------------------------------------------------------

void Renderer<FlatVertex>::Terminate()
{
	Assert(!m_Rendering, "Rendering!");
	m_VertexShader.Release();
	m_PixelShader.Release();
	m_CameraBuffer.Free();
	m_Initialized = false;
}

//---------------------------------------------------------------------------

void Renderer<FlatVertex>::StartRendering(const Camera& p_Camera)
{
	Assert(m_Initialized, "Not initialized!");
	m_CameraBuffer.Data.WorldPosition = MakeAffinePoint(p_Camera.Transform.GetPosition());
	m_CameraBuffer.Data.WorldToProjection = p_Camera.GetWorldToPerspectiveTransform(static_cast<f32>(m_System.GetAspectRatio())).Transposition();
	m_VertexShader.Bind();
	m_PixelShader.Bind();
	m_CameraBuffer.Update();
	m_CameraBuffer.BindToVertexShader(0);
	m_Rendering = true;
}

//---------------------------------------------------------------------------

void Renderer<FlatVertex>::Render(const VertexBuffer<FlatVertex>& p_Buffer
	, Mathematics::TopologyIndexing p_Toplogy)
{
	Assert(m_Rendering, "Not rendering!");
	Assert(m_Initialized, "Not initialized!");
	p_Buffer.Bind();
	p_Buffer.Draw(p_Toplogy);
}

//---------------------------------------------------------------------------

void Renderer<FlatVertex>::StopRendering()
{
	Assert(m_Rendering, "Not rendering!");
	Assert(m_Initialized, "Not initialized!");
	m_PixelShader.Unbind();
	m_VertexShader.Unbind();
	m_Rendering = false;
}