//===========================================================================
// Filename:	PaintedRenderer.cpp
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


Renderer<PaintedVertex>::Renderer(System& p_System)
	: m_VertexShader(p_System)
	, m_PixelShader(p_System)
	, m_PostProcessBuffer(p_System)
	, m_ObjectBuffer(p_System)
	, m_RenderTarget(p_System)
	, m_TextureSampler()
	, m_RenderQuad(p_System)
	, m_Initialized(false)
	, m_Rendering(false)
	, m_System(p_System)
{}

//---------------------------------------------------------------------------

Renderer<PaintedVertex>::~Renderer()
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(!m_Initialized, "Still initialized!");
}

//---------------------------------------------------------------------------

void Renderer<PaintedVertex>::Initialize()
{
	Assert(!m_Initialized, "Already initialized!");
	Assert(!m_Rendering, "Currently rendering!");
	m_VertexShader.Compile();
	m_PixelShader.Compile();
	m_PostProcessBuffer.Allocate(nullptr);
	ShaderInformation::PerObjectConstants object;
	object.Colour = ColourPallet::Gray25;
	m_ObjectBuffer.Allocate(&object);

	m_RenderTarget.Initialize(m_System.GetWidth(), m_System.GetHeight(), RenderTarget::Format::RGBA_U8);
	m_TextureSampler.Initialize(m_System, Sampler::Filter::Linear, Sampler::AddressMode::Clamp);

	//build screen quad
	PaintedMesh renderTargetMesh;
	renderTargetMesh.Allocate(4, 6, TopologyIndexing::TriangleList);

	renderTargetMesh.GetVertex(0).Position = MakeVector(-Unity, -Unity, Zero);
	renderTargetMesh.GetVertex(1).Position = MakeVector(-Unity, Unity, Zero);
	renderTargetMesh.GetVertex(2).Position = MakeVector(Unity, Unity, Zero);
	renderTargetMesh.GetVertex(3).Position = MakeVector(Unity, -Unity, Zero);

	renderTargetMesh.GetVertex(0).TextureCoord = V();
	renderTargetMesh.GetVertex(1).TextureCoord = Zero2();
	renderTargetMesh.GetVertex(2).TextureCoord = U();
	renderTargetMesh.GetVertex(3).TextureCoord = Ones2();

	renderTargetMesh.GetIndex(0) = 0;
	renderTargetMesh.GetIndex(1) = 1;
	renderTargetMesh.GetIndex(2) = 2;
	renderTargetMesh.GetIndex(3) = 0;
	renderTargetMesh.GetIndex(4) = 2;
	renderTargetMesh.GetIndex(5) = 3;

	m_RenderQuad.Initialize(renderTargetMesh);
	renderTargetMesh.Destroy();

	m_Initialized = true;
}

//---------------------------------------------------------------------------

void Renderer<PaintedVertex>::Terminate()
{
	Assert(m_Initialized, "Not initialized!");
	Assert(!m_Rendering, "Currently rendering!");

	m_RenderQuad.Terminate();

	m_RenderTarget.Terminate();
	m_TextureSampler.Terminate();

	m_ObjectBuffer.Free();
	m_PostProcessBuffer.Free();

	m_PixelShader.Release();
	m_VertexShader.Release();

	m_Initialized = false;
}

//---------------------------------------------------------------------------

void Renderer<PaintedVertex>::BindRenderTarget()
{
	Assert(m_Initialized, "Not initialized!");
	Assert(!m_Rendering, "Currently rendering!");
	m_RenderTarget.BeginRender();
	m_Rendering = true;
}

//---------------------------------------------------------------------------

void Renderer<PaintedVertex>::UnbindRenderTarget()
{
	Assert(m_Initialized, "Not initialized!");
	Assert(m_Rendering, "Not rendering!");
	m_RenderTarget.EndRender();
	m_Rendering = false;
}

//---------------------------------------------------------------------------

void Renderer<PaintedVertex>::Render()
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(m_Initialized, "Not initialized!");

	m_PostProcessBuffer.Update();
	m_PostProcessBuffer.BindToPixelShader(0);
	m_ObjectBuffer.BindToPixelShader(1);

	m_VertexShader.Bind();
	m_PixelShader.Bind();

	m_TextureSampler.BindPixelShader(m_System, 0);

	m_RenderTarget.BindTexture(0);
	m_RenderQuad.m_VertexBuffer.Bind();
	m_RenderQuad.m_IndexBuffer.Draw(m_RenderQuad.m_Topology);
	m_RenderTarget.UnbindTexture(0);
}

//---------------------------------------------------------------------------

const char* Renderer<PaintedVertex>::GetEffectName() const
{
	static const char* effectNames[numEffects] =
	{ "Unprocessed"
	, "Red Monochrome"
	, "Green Monochrome"
	, "Blue Monochrome"
	, "Grayscale"
	, "Vignette"
	, "Fish Eye"
	, "Infrared"
	, "Flat Blur"
	, "Photo Negative"
	, "Linearized Depth"};

	return effectNames[m_PostProcessBuffer.Data.Index];
}

//---------------------------------------------------------------------------

void Renderer<PaintedVertex>::NextEffect()
{
	(m_PostProcessBuffer.Data.Index += 1) %= numEffects;
}

//---------------------------------------------------------------------------

void Renderer<PaintedVertex>::LastEffect()
{
	(m_PostProcessBuffer.Data.Index -= 1) %= numEffects;
}