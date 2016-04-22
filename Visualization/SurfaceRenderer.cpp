//===========================================================================
// Filename:	SurfaceRenderer.cpp
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


Renderer<SurfaceVertex>::Renderer(System& p_System)
	: m_VertexShader(p_System)
	, m_PixelShader(p_System)
	, m_CameraBuffer(p_System)
	, m_WaterBuffer(p_System)
	, m_LightBuffer(p_System)
	, m_ReflectionMap(p_System)
	, m_RefractionMap(p_System)
	, m_TextureSampler()
	, m_Initialized(false)
	, m_Rendering(false)
	, m_System(p_System)
{}

Renderer<SurfaceVertex>::~Renderer() 
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(!m_Initialized, "Still initialized!");
}

void Renderer<SurfaceVertex>::Initialize()
{
	m_VertexShader.Compile();
	m_PixelShader.Compile();

	m_CameraBuffer.Allocate();
	m_WaterBuffer.Allocate();
	m_LightBuffer.Allocate();

	m_ReflectionMap.Initialize(m_System.GetWidth(), m_System.GetHeight(), RenderTarget::Format::RGBA_U8);
	m_RefractionMap.Initialize(m_System.GetWidth(), m_System.GetHeight(), RenderTarget::Format::RGBA_U8);

	m_TextureSampler.Initialize(m_System, Sampler::Filter::Linear, Sampler::AddressMode::Border);

	m_Initialized = true;
}

void Renderer<SurfaceVertex>::Terminate()
{
	m_TextureSampler.Terminate();

	m_RefractionMap.Terminate();
	m_ReflectionMap.Terminate();

	m_LightBuffer.Free();
	m_WaterBuffer.Free();
	m_CameraBuffer.Free();

	m_PixelShader.Release();
	m_VertexShader.Release();

	m_Initialized = false;
}

void Renderer<SurfaceVertex>::StartRendering(const Camera& p_Camera)
{
	Assert(!m_Rendering, "Already rendering!");
	Assert(m_Initialized, "Not initialized!");

	m_CameraBuffer.Data.WorldPosition = MakeAffinePoint(p_Camera.Transform.GetPosition());
	m_CameraBuffer.Data.WorldToProjection = p_Camera.GetWorldToPerspectiveTransform(static_cast<f32>(m_System.GetAspectRatio())).Transposition();

	m_CameraBuffer.Update();

	m_CameraBuffer.BindToVertexShader(0);

	m_LightBuffer.BindToVertexShader(2);
	m_LightBuffer.BindToPixelShader(2);

	m_TextureSampler.BindVertexShader(m_System, 0);
	m_TextureSampler.BindPixelShader(m_System, 0);

	m_VertexShader.Bind();
	m_PixelShader.Bind();

	m_ReflectionMap.BindTexture(0);
	m_RefractionMap.BindTexture(1);

	m_Rendering = true;
}

void Renderer<SurfaceVertex>::StopRendering()
{
	Assert(m_Rendering, "Not rendering!");
	Assert(m_Initialized, "Not initialized!");
	m_Rendering = false;
}

void Renderer<SurfaceVertex>::StartRefractionMapping(const Camera& p_Camera)
{
	Assert(m_Initialized, "Not initialized!");
	Assert(!m_Rendering, "Currently rendering!");
	m_RefractionWorldToView = p_Camera.GetWorldToViewTransform();
	m_RefractionProjection = p_Camera.GetViewToPerspectiveTransform(static_cast<f32>(m_System.GetAspectRatio()));
	m_RefractionMap.BeginRender();
}

void Renderer<SurfaceVertex>::StopRefractionMapping()
{
	Assert(m_Initialized, "Not initialized!");
	Assert(!m_Rendering, "Not rendering!");
	m_RefractionMap.EndRender();
}

void Renderer<SurfaceVertex>::StartReflectionMapping(const Camera& p_Camera)
{
	Assert(m_Initialized, "Not initialized!");
	Assert(!m_Rendering, "Currently rendering!");
	m_ReflectionWorldToView = p_Camera.GetWorldToViewTransform();
	m_ReflectionProjection = p_Camera.GetViewToPerspectiveTransform(static_cast<f32>(m_System.GetAspectRatio()));
	m_ReflectionMap.BeginRender();
}

void Renderer<SurfaceVertex>::StopReflectionMapping()
{
	Assert(m_Initialized, "Not initialized!");
	Assert(!m_Rendering, "Not rendering!");
	m_ReflectionMap.EndRender();
}

void Renderer<SurfaceVertex>::RegisterLight(const Light& p_Light)
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(m_Initialized, "Not initialized!");

	m_LightBuffer.Data.LightColour = p_Light.Diffuse;
	m_LightBuffer.Data.LightWorldDirection = p_Light.Position;
	m_LightBuffer.Data.WorldAmbient = p_Light.Ambient;

	m_LightBuffer.Update();
}

void Renderer<SurfaceVertex>::Update(f32 p_Time)
{
	m_WaterBuffer.Data.Time = p_Time;
}

void Renderer<SurfaceVertex>::RenderModel(const Mathematics::Frame& p_Frame,
	const SolidModel<SurfaceVertex>& p_Model)
{
	Mathematics::Matrix44 locToWorld = p_Frame.GetLocalToWorld();
	Mathematics::Matrix44 locToWorldTransp = locToWorld.Transposition();
	m_WaterBuffer.Data.LocalToProjection = locToWorldTransp * m_CameraBuffer.Data.WorldToProjection;
	m_WaterBuffer.Data.LocalToWorld = locToWorldTransp;
	m_WaterBuffer.Data.WorldToLocalTranpose = locToWorld;
	m_WaterBuffer.Data.Colour = ColourPallet::LightBlue4.SetAlpha(0.50f);
	m_WaterBuffer.Data.ReflectionLocalToTangent = (m_ReflectionWorldToView * locToWorld).Transposition();
	m_WaterBuffer.Data.RefractionLocalToTangent = (m_RefractionWorldToView * locToWorld).Transposition();
	m_WaterBuffer.Data.Wave1 = MakeVector(1.0, 1.0, 1.2f, 7.0f); //direction x, y, amplitude, frequency
	m_WaterBuffer.Data.Wave2 = MakeVector(1.0, 0.0, 0.8f, 10.0f);  //direction x, y, amplitude, frequency
	m_WaterBuffer.Data.Wave3 = MakeVector(0.0, -1.0, 1.2f, 5.0f);  //direction x, y, amplitude, frequency

	m_WaterBuffer.Update();

	m_WaterBuffer.BindToVertexShader(1);
	m_WaterBuffer.BindToPixelShader(1);

	p_Model.m_VertexBuffer.Bind();
	p_Model.m_IndexBuffer.Draw(p_Model.m_Topology);
}