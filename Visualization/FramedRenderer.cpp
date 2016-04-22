//===========================================================================
// Filename:	FramedRenderer.cpp
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

Renderer<FramedVertex>::Renderer(System& p_System)
	: m_VertexShader(p_System)
	, m_DepthMapper(p_System)
	, m_StandardPixelShader(p_System)
	, m_CelPixelShader(p_System)
	, m_FancyPixelShader(p_System)
	, m_ObjectBuffer(p_System)
	, m_LightBuffer(p_System)
	, m_CameraBuffer(p_System)
	, m_MaterialBuffer(p_System)
	, m_DefaultMaterial()
	, m_GradientMap()
	, m_DepthMap(p_System)
	, m_TextureSampler()
	, m_DepthSampler()
	, m_Sphere(p_System)
	, m_Torus(p_System)
	, m_CurrentShading(Shading::Default)
	, m_Initialized(false)
	, m_Rendering(false)
	, m_System(p_System)
{}

//---------------------------------------------------------------------------

Renderer<FramedVertex>::~Renderer()
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(!m_Initialized, "Still initialized!");
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::Initialize()
{
	Assert(!m_Initialized, "Already initialized!");
	Assert(!m_Rendering, "Currently rendering!");

	m_VertexShader.Compile();
	m_DepthMapper.Compile();
	m_StandardPixelShader.Compile();
	m_CelPixelShader.Compile();
	m_FancyPixelShader.Compile();

	m_ObjectBuffer.Allocate();
	m_LightBuffer.Allocate();
	m_CameraBuffer.Allocate();
	m_MaterialBuffer.Allocate();

	m_DefaultMaterial.Initialize(m_System);
	m_GradientMap.Initialize(m_System, L"../Data/Images/gradient_map.jpg");
	m_DepthMap.Initialize(m_System.GetWidth(), m_System.GetHeight());

	m_TextureSampler.Initialize(m_System, Sampler::Filter::Linear
		, Sampler::AddressMode::Wrap);
	m_DepthSampler.Initialize(m_System, Sampler::Filter::Point
		, Sampler::AddressMode::Border);

	Mesh<FramedVertex> sphereMesh;
	MeshBuilder::CreateUnitSphere(sphereMesh, 32);

	m_Sphere.Initialize(sphereMesh);

	sphereMesh.Destroy();

	MeshBuilder::CreateUnitTorus(sphereMesh, 16);

	m_Torus.Initialize(sphereMesh);
	sphereMesh.Destroy();

	m_Initialized = true;
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::Terminate()
{
	Assert(m_Initialized, "Not initialized!");
	Assert(!m_Rendering, "Currently rendering!");

	m_Sphere.Terminate();
	m_Torus.Terminate();

	m_DepthSampler.Terminate();
	m_TextureSampler.Terminate();

	m_DepthMap.Terminate();
	m_GradientMap.Terminate();
	m_DefaultMaterial.Terminate();

	m_MaterialBuffer.Free();
	m_CameraBuffer.Free();
	m_LightBuffer.Free();
	m_ObjectBuffer.Free();

	m_FancyPixelShader.Release();
	m_CelPixelShader.Release();
	m_StandardPixelShader.Release();

	m_DepthMapper.Release();
	m_VertexShader.Release();

	m_Initialized = false;
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::StartRenderingOrtho(const Camera& p_Camera, const u32 p_ScreenWidth, const u32 p_ScreenHeight)
{
	Time("FrameVertexStartRenderingOrtho");

	m_CameraBuffer.Data.WorldPosition = MakeAffinePoint(p_Camera.Transform.GetPosition());
	m_CameraBuffer.Data.WorldToProjection = p_Camera.GetWorldToOrthogonalTransform(p_ScreenWidth, p_ScreenHeight).Transposition();

	m_CameraBuffer.Update();

	StartShadingInternal();
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::StartRenderingPersp(const Camera& p_Camera)
{
	Time("FrameVertexStartRenderingPersp");

	m_CameraBuffer.Data.WorldPosition = MakeAffinePoint(p_Camera.Transform.GetPosition());
	m_CameraBuffer.Data.WorldToProjection = p_Camera.GetWorldToPerspectiveTransform(static_cast<f32>(m_System.GetAspectRatio())).Transposition();

	m_CameraBuffer.Update();

	StartShadingInternal();
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::StopRendering()
{
	Assert(m_Rendering, "Not rendering!");
	Assert(m_Initialized, "Not initialized!");

	m_Rendering = false;
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::SwitchShading(const Shading p_ShadingType)
{
	Assert(m_Rendering, "Not rendering!");
	Assert(m_Initialized, "Not initialized!");

	if (p_ShadingType == m_CurrentShading)
	{
		return;
	}

	//remove specific sources
	if (Shading::Default == m_CurrentShading)
	{
		m_StandardPixelShader.Unbind();
	}
	else if (Shading::Cel == m_CurrentShading)
	{
		m_GradientMap.UnbindPixelShader(m_System, 7);
		m_CelPixelShader.Unbind();
	}
	else if (Shading::Fancy == m_CurrentShading)
	{
		m_DefaultMaterial.m_EmissiveTexture.UnbindPixelShader(m_System, 4);
		m_DefaultMaterial.m_UmbralTexture.UnbindPixelShader(m_System, 5);
		m_FancyPixelShader.Unbind();
	}

	//add specific sources
	if (Shading::Default == p_ShadingType)
	{
		m_StandardPixelShader.Bind();
	}
	else if (Shading::Cel == p_ShadingType)
	{
		m_CelPixelShader.Bind();
		m_GradientMap.BindPixelShader(m_System, 7);
	}
	else if (Shading::Fancy == p_ShadingType)
	{
		m_FancyPixelShader.Bind();
		m_DefaultMaterial.m_EmissiveTexture.BindPixelShader(m_System, 4);
		m_DefaultMaterial.m_UmbralTexture.BindPixelShader(m_System, 5);
	}
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::StartDepthMapping()
{
	Halt("Stubbed!");
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::StopDepthMapping()
{
	Halt("Stubbed!");
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::RegisterLight(const Light& p_Light)
{
	Assert(!m_Rendering, "Currently rendering!");
	Assert(m_Initialized, "Not initialized!");

	m_LightBuffer.Data.LightColour = p_Light.Diffuse;
	m_LightBuffer.Data.LightWorldDirection = p_Light.Position;
	m_LightBuffer.Data.WorldAmbient = p_Light.Ambient;

	m_LightBuffer.Update();
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::BindMaterial(const Material& p_Material)
{
	Assert(m_Rendering, "Not rendering!");
	Assert(m_Initialized, "Not initialized!");
	Assert(m_CurrentShading != Shading::Fancy, "Cant use basic matrial!");

	p_Material.m_BumpTexture.BindVertexShader(m_System, 0);
	p_Material.m_DiffuseTexture.BindPixelShader(m_System, 1);
	p_Material.m_SpecularTexture.BindPixelShader(m_System, 2);
	p_Material.m_NormalTexture.BindPixelShader(m_System, 3);

	m_MaterialBuffer.Data.Ambient = p_Material.m_Ambient;
	m_MaterialBuffer.Data.Diffuse = p_Material.m_Diffuse;
	m_MaterialBuffer.Data.Specular = p_Material.m_Specular;
	m_MaterialBuffer.Data.Emissive = Mathematics::ColourPallet::Black;
	m_MaterialBuffer.Data.Reflectance = p_Material.m_Reflectance;
	m_MaterialBuffer.Update();

	m_MaterialBuffer.BindToPixelShader(3);
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::BindMaterial(const FancyMaterial& p_Material)
{
	Assert(m_Rendering, "Not rendering!");
	Assert(m_Initialized, "Not initialized!");

	p_Material.m_BumpTexture.BindVertexShader(m_System, 0);
	p_Material.m_DiffuseTexture.BindPixelShader(m_System, 1);
	p_Material.m_SpecularTexture.BindPixelShader(m_System, 2);
	p_Material.m_NormalTexture.BindPixelShader(m_System, 3);
	p_Material.m_EmissiveTexture.BindPixelShader(m_System, 4);
	p_Material.m_UmbralTexture.BindPixelShader(m_System, 5);

	m_MaterialBuffer.Data.Ambient = p_Material.m_Ambient;
	m_MaterialBuffer.Data.Diffuse = p_Material.m_Diffuse;
	m_MaterialBuffer.Data.Specular = p_Material.m_Specular;
	m_MaterialBuffer.Data.Emissive = p_Material.m_Emissive;
	m_MaterialBuffer.Data.Reflectance = p_Material.m_Reflectance;
	m_MaterialBuffer.Update();

	m_MaterialBuffer.BindToPixelShader(3);
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::RenderModel(const Mathematics::Frame& p_Frame,
	const SolidModel<FramedVertex>& p_Model)
{
	Mathematics::Matrix44 locToWorldTransp = p_Frame.GetLocalToWorld().Transposition();
	m_ObjectBuffer.Data.LocalToProjection = locToWorldTransp * m_CameraBuffer.Data.WorldToProjection;
	m_ObjectBuffer.Data.LocalToWorld = locToWorldTransp;
	m_ObjectBuffer.Data.WorldToLocalTranpose = p_Frame.GetLocalToWorld();

	m_ObjectBuffer.Update();

	m_ObjectBuffer.BindToVertexShader(1);
	m_ObjectBuffer.BindToPixelShader(1);

	p_Model.m_VertexBuffer.Bind();
	p_Model.m_IndexBuffer.Draw(p_Model.m_Topology);
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::RenderModel(const Mathematics::Frame& p_Frame,
	const MeshModel<FramedVertex>& p_Model)
{
	Halt("Stubbed!");
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::RenderSphere(const Mathematics::Frame& p_Frame
	, const f32 p_Radius)
{
	Mathematics::Matrix44 locToWorldTransp = (p_Frame.GetLocalToWorld() * MakeScaling(p_Radius)).Transposition();
	m_ObjectBuffer.Data.LocalToProjection = locToWorldTransp * m_CameraBuffer.Data.WorldToProjection;
	m_ObjectBuffer.Data.LocalToWorld = locToWorldTransp;
	m_ObjectBuffer.Data.WorldToLocalTranpose = p_Frame.GetLocalToWorld();

	m_ObjectBuffer.Update();

	RenderSphereInternal();
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::RenderTorus(const Mathematics::Frame& p_Frame
	, const f32 p_Radius)
{
	Mathematics::Matrix44 locToWorldTransp = (p_Frame.GetLocalToWorld() * MakeScaling(p_Radius)).Transposition();
	m_ObjectBuffer.Data.LocalToProjection = locToWorldTransp * m_CameraBuffer.Data.WorldToProjection;
	m_ObjectBuffer.Data.LocalToWorld = locToWorldTransp;
	m_ObjectBuffer.Data.WorldToLocalTranpose = p_Frame.GetLocalToWorld();

	m_ObjectBuffer.Update();

	RenderTorusInternal();
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::RenderSphere(const Mathematics::Sphere3& p_Sphere
	, const Mathematics::Quaternion& p_Orientation)
{
	Mathematics::Matrix44 locToWorld = MakeTransformation(p_Sphere.Centre, p_Orientation, p_Sphere.Radius);
	Mathematics::Matrix44 locToWorldTransp = locToWorld.Transposition();
	m_ObjectBuffer.Data.LocalToProjection = locToWorldTransp * m_CameraBuffer.Data.WorldToProjection;
	m_ObjectBuffer.Data.LocalToWorld = locToWorldTransp;
	m_ObjectBuffer.Data.WorldToLocalTranpose = locToWorld;

	m_ObjectBuffer.Update();

	RenderSphereInternal();
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::StartShadingInternal()
{
	Assert(!m_Rendering, "Already rendering!");
	Assert(m_Initialized, "Not initialized!");

	m_CameraBuffer.BindToVertexShader(0);

	m_LightBuffer.BindToVertexShader(2);
	m_LightBuffer.BindToPixelShader(2);

	m_TextureSampler.BindVertexShader(m_System, 0);
	m_TextureSampler.BindPixelShader(m_System, 0);

	m_DepthSampler.BindPixelShader(m_System, 1);

	m_VertexShader.Bind();

	m_StandardPixelShader.Bind();

	m_Rendering = true;

	BindMaterial(m_DefaultMaterial);
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::RenderSphereInternal()
{
	m_ObjectBuffer.BindToVertexShader(1);
	m_ObjectBuffer.BindToPixelShader(1);

	m_Sphere.m_VertexBuffer.Bind();
	m_Sphere.m_IndexBuffer.Draw(m_Sphere.m_Topology);
}

//---------------------------------------------------------------------------

void Renderer<FramedVertex>::RenderTorusInternal()
{
	m_ObjectBuffer.BindToVertexShader(1);
	m_ObjectBuffer.BindToPixelShader(1);

	m_Torus.m_VertexBuffer.Bind();
	m_Torus.m_IndexBuffer.Draw(m_Torus.m_Topology);
}