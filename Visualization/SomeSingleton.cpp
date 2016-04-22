//===========================================================================
// Filename:	SomeSingleton.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include <Mathematics.h>
#include "SomeSingleton.h"
#include "GraphicBasic.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "RenderTarget.h"
#include "DepthMap.h"

using namespace Mathematics;
using namespace Visualization;

//===========================================================================
// Implementation Declarations
//===========================================================================

//namespace
//{
//
//	namespace Details
//	{
//		//states
//		static bool s_DrawingScene;
//		static bool s_MappingDepth;
//
//		//
//		static Mathematics::Frame s_PostProcessFrame;
//
//		//lighting
//		Vector3 casterPosition = MakeVector(14.0f, 6.0f, 6.0f) * 0.95f;
//		Vector3 lightDirection = MakeVector(1.0f, -1.0f, 1.0f);
//		f32 lightDistance = 100.0f;
//		Vector3 lightPosition = casterPosition - (lightDirection * lightDistance);
//
//		Matrix44 i_NDCtoUV = MakeMatrix(0.5f, Zero, Zero, 0.5f
//										, Zero, -0.5f, Zero, 0.5f
//										, Zero, Zero, Unity, Zero
//										, Zero, Zero, Zero, Unity);
//
//		std::unique_ptr<SomeSingletonImplementation> s_Implementation;
//	}
//
//	class SomeSingletonImplementation
//	{
//		//Operators
//	public:
//
//		SomeSingletonImplementation(::System& p_System);
//
//		~SomeSingletonImplementation();
//
//		//Functions
//	public:
//
//		void Initialize();
//		void Terminate();
//
//		//rendering
//		void StartRenderMapping();
//		void StopRenderMapping();
//		void StartDepthMapping();
//		void StopDepthMapping();
//		void BindRenderTarget(const u32 p_Slot = 0);
//		void UnbindRenderTarget(const u32 p_Slot = 0);
//		void BindDepthMap(const u32 p_Slot = 4);
//		void UnbindDepthMap(const u32 p_Slot = 4);
//		void LightDepthRender();
//		void PostProcessRender();
//
//		//utils
//		void SetShading(SomeSingleton::ShadingMode p_Mode);
//
//		void BindShader();
//
//		void BindMaterial(const Material& p_Material);
//
//		//solids
//		void DrawSphere(const Mathematics::Matrix44& p_Transform);
//		void DrawTorus(const Mathematics::Matrix44& p_Transform);
//
//		//defaults
//		const Material& DefaultMaterial() const { return m_DefaultMaterial; }
//
//		//Attributes
//	private:
//
//		//lighting
//		Camera m_LightCamera;
//
//		//solids
//		Material m_DefaultMaterial;
//		FramedSolid m_FramedSphere;
//		FramedSolid m_FramedTorus;
//
//		//shaders
//		VertexShader<FramedVertex> m_FramedVS;
//		VertexShader<FramedVertex> m_MapDepthVS;
//		VertexShader<PaintedVertex> m_PostProcessVS;
//
//		PixelShader m_FramedPS;
//		PixelShader m_MapDepthPS;
//		PixelShader m_PostProcessPS;
//
//		//mapping
//		PaintedSolid m_RenderTargetQuad;
//		RenderTarget m_RenderTarget;
//		DepthMap m_DepthMap;
//		PostProcessConstantBuffer m_PostProcessBuffer;
//		Texture m_CelGradient;
//
//		SomeSingleton::ShadingMode m_Mode;
//		::System& m_System;
//		bool m_Initialized;
//
//	public:
//
//		bool ShadowsOn;
//		bool PostProcessingOn;
//		bool CelShadingOn;
//	};
//
//	//===========================================================================
//	// Implementation Definitions
//	//===========================================================================
//
//	SomeSingletonImplementation::SomeSingletonImplementation(::System& p_System)
//		: m_LightCamera(p_System)
//		, m_DefaultMaterial(p_System)
//		, m_FramedSphere(p_System)
//		, m_FramedTorus(p_System)
//		, m_FramedVS(p_System)
//		, m_MapDepthVS(p_System)
//		, m_PostProcessVS(p_System)
//		, m_FramedPS(p_System)
//		, m_MapDepthPS(p_System)
//		, m_PostProcessPS(p_System)
//		, m_RenderTargetQuad(p_System)
//		, m_RenderTarget(p_System)
//		, m_DepthMap(p_System)
//		, m_PostProcessBuffer(p_System)
//		, m_CelGradient(p_System)
//		, m_Mode(SomeSingleton::ShadingMode::None)
//		, m_System(p_System)
//		, m_Initialized(false)
//		, ShadowsOn(true)
//		, PostProcessingOn(true)
//		, CelShadingOn(false)
//	{}
//
//	SomeSingletonImplementation::~SomeSingletonImplementation()
//	{
//		Assert(!m_Initialized, "Still initialized!");
//	}
//
//	void SomeSingletonImplementation::Initialize()
//	{
//		Assert(!m_Initialized, "Already initialized!");
//
//		//solids
//		LitMesh litMeshData;
//		MeshBuilder::CreateUnitSphere(litMeshData, 8);
//		//m_LitSphere.Initialize(litMeshData);
//		litMeshData.Destroy();
//
//		FramedMesh framedMeshData;
//		MeshBuilder::CreateUnitSphere(framedMeshData, 16);
//		m_FramedSphere.Initialize(framedMeshData);
//		framedMeshData.Destroy();
//
//		MeshBuilder::CreateUnitTorus(framedMeshData, 16);
//		m_FramedTorus.Initialize(framedMeshData);
//		framedMeshData.Destroy();
//
//		m_RenderTarget.Initialize(m_System.GetWidth(), m_System.GetHeight(), RenderTarget::Format::RGBA_U8);
//		m_DepthMap.Initialize(m_System.GetWidth(), m_System.GetHeight());
//
//		m_DefaultMaterial.Initialize();
//
//		//shaders
//		m_FramedVS.Compile(L"../Data/Shaders/ShadedLighting.fx", "VS", "vs_4_0");
//		m_FramedPS.Compile(L"../Data/Shaders/ShadedLighting.fx", "PS", "ps_4_0");
//
//		m_MapDepthVS.Compile(L"../Data/Shaders/MapDepth.fx", "VS", "vs_4_0");
//
//		m_PostProcessVS.Compile(L"../Data/Shaders/PostProcess.fx", "VS", "vs_4_0");
//		m_PostProcessPS.Compile(L"../Data/Shaders/PostProcess.fx", "PS", "ps_4_0");
//
//		m_CelGradient.Initialize(L"../Data/Images/gradient_map.jpg");
//
//		m_ShadowBuffer.Allocate();
//
//		LightingInfo lights;
//		m_LightCamera.Initialize(Details::lightPosition, Details::casterPosition
//								 , 500.0f, PiOverTwo, true, 1.0f); //aspect ratio = 1.0f!!!
//		lights.LightDirection = MakeAffineVector(Details::lightDirection);
//		lights.LightAmbient = ColourPallet::White;
//		lights.LightDiffuse = ColourPallet::White;
//		lights.LightSpecular = ColourPallet::White;
//		m_LightingBuffer.Allocate(&lights);
//
//		m_PostProcessBuffer.Data[0].EffectIndex = -1;
//		m_PostProcessBuffer.Data[0].Height = static_cast<f32>(m_System.GetHeight());
//		m_PostProcessBuffer.Data[0].Intensity = 1.0f;
//		m_PostProcessBuffer.Data[0].Width = static_cast<f32>(m_System.GetWidth());
//		m_PostProcessBuffer.Data[0].DetectEdges = false;
//		m_PostProcessBuffer.Allocate();
//
//
//		//render target mesh
//		PaintedMesh renderTargetMesh;
//		renderTargetMesh.Allocate(4, 6, TopologyIndexing::TriangleList);
//
//		renderTargetMesh.GetVertex(0).Position = MakeVector(-Unity, -Unity, Zero);
//		renderTargetMesh.GetVertex(1).Position = MakeVector(-Unity, Unity, Zero);
//		renderTargetMesh.GetVertex(2).Position = MakeVector(Unity, Unity, Zero);
//		renderTargetMesh.GetVertex(3).Position = MakeVector(Unity, -Unity, Zero);
//
//		renderTargetMesh.GetVertex(0).TextureCoord = V();
//		renderTargetMesh.GetVertex(1).TextureCoord = Zero2();
//		renderTargetMesh.GetVertex(2).TextureCoord = U();
//		renderTargetMesh.GetVertex(3).TextureCoord = Ones2();
//
//		renderTargetMesh.GetIndex(0) = 0;
//		renderTargetMesh.GetIndex(1) = 1;
//		renderTargetMesh.GetIndex(2) = 2;
//		renderTargetMesh.GetIndex(3) = 0;
//		renderTargetMesh.GetIndex(4) = 2;
//		renderTargetMesh.GetIndex(5) = 3;
//
//		m_RenderTargetQuad.Initialize(renderTargetMesh);
//		renderTargetMesh.Destroy();
//
//		m_Initialized = true;
//	}
//
//	void SomeSingletonImplementation::Terminate()
//	{
//		Assert(m_Initialized, "Not initialized!");
//
//		m_Initialized = false;
//
//		m_CelGradient.Terminate();
//
//		m_LightingBuffer.Free();
//		m_LightCamera.Terminate();
//
//		m_LitVS.Release();
//		m_LitPS.Release();
//
//		m_ShadedVS.Release();
//		m_ShadedPS.Release();
//
//		m_ShadedLitVS.Release();
//		m_ShadedLitPS.Release();
//
//		m_FullyShadedVS.Release();
//		m_FullyShadedPS.Release();
//
//		m_MapDepthVS.Release();
//
//		m_PostProcessPS.Release();
//		m_PostProcessVS.Release();
//		 
//		m_FullyShadedWithCelPS.Release();
//		
//		m_ShadowBuffer.Free();
//		m_PostProcessBuffer.Free();
//
//		m_RenderTargetQuad.Terminate();
//		m_DepthMap.Terminate();
//		m_RenderTarget.Terminate();
//
//		m_DefaultMaterial.Terminate();
//
//		m_FullyShadedTorus.Terminate();
//		m_FullyShadedSphere.Terminate();
//		m_LitSphere.Terminate();
//	}
//	void SomeSingletonImplementation::StartRenderMapping()
//	{
//		m_RenderTarget.BeginRender();
//	}
//
//	void SomeSingletonImplementation::StopRenderMapping()
//	{
//		m_RenderTarget.EndRender();
//	}
//
//	void SomeSingletonImplementation::StartDepthMapping()
//	{
//		Details::s_MappingDepth = true;
//		m_DepthMap.BeginRender();
//
//		Details::s_ShadowInfo.WorldToProjection = Details::i_NDCtoUV * m_LightCamera.GetWorldToPerspectiveTransform();
//	}
//
//	void SomeSingletonImplementation::StopDepthMapping()
//	{
//		m_DepthMap.EndRender();
//		Details::s_MappingDepth = false;
//	}
//
//	void SomeSingletonImplementation::BindRenderTarget(const u32 p_Slot)
//	{
//		m_RenderTarget.BindTexture(p_Slot);
//	}
//	void SomeSingletonImplementation::UnbindRenderTarget(const u32 p_Slot)
//	{
//		m_RenderTarget.UnbindTexture(p_Slot);
//	}
//
//	void SomeSingletonImplementation::BindDepthMap(const u32 p_Slot)
//	{
//		m_DepthMap.BindTexture(p_Slot);
//	}
//	void SomeSingletonImplementation::UnbindDepthMap(const u32 p_Slot)
//	{
//		m_DepthMap.UnbindTexture(p_Slot);
//	}
//
//	void SomeSingletonImplementation::LightDepthRender()
//	{
//		SetShading(::SomeSingleton::ShadingMode::Postprocessing);
//		m_PostProcessBuffer.Set(&Details::s_PostProcessInfo);
//		m_PostProcessBuffer.BindToPixelShader(0);
//
//		BindDepthMap(0);
//
//		m_RenderTargetQuad.Render(Details::s_PostProcessFrame.GetLocalToWorld());
//
//		UnbindDepthMap(0);
//	}
//
//	void SomeSingletonImplementation::PostProcessRender()
//	{
//		SetShading(::SomeSingleton::ShadingMode::Postprocessing);
//		m_PostProcessBuffer.Set(&Details::s_PostProcessInfo);
//		m_PostProcessBuffer.BindToPixelShader(0);
//
//		BindRenderTarget();
//
//		m_RenderTargetQuad.Render(Details::s_PostProcessFrame.GetLocalToWorld());
//
//		UnbindRenderTarget();
//	}
//
//	void SomeSingletonImplementation::SetShading(SomeSingleton::ShadingMode p_Mode)
//	{
//		Time("SetShading");
//
//		if(m_Mode != p_Mode)
//		{
//			m_Mode = p_Mode;
//			BindShader();
//		}
//	}
//
//	void SomeSingletonImplementation::BindShader()
//	{
//		Time("BindShader");
//		switch(m_Mode)
//		{
//		case Visualization::SomeSingleton::ShadingMode::Lit:
//		m_LitVS.Bind();
//		m_LitPS.Bind();
//		break;
//		case Visualization::SomeSingleton::ShadingMode::Shading:
//		m_ShadedVS.Bind();
//		m_ShadedPS.Bind();
//		m_TextureSampler.BindPixelShader(m_System, 0);
//		break;
//		case Visualization::SomeSingleton::ShadingMode::LitShading:
//		m_ShadedLitVS.Bind();
//		m_ShadedLitPS.Bind();
//		m_TextureSampler.BindVertexShader(m_System, 0);
//		m_TextureSampler.BindPixelShader(m_System, 0);
//		break;
//		case Visualization::SomeSingleton::ShadingMode::FullShading:
//		m_FullyShadedVS.Bind();
//		if(CelShadingOn)
//		{
//			m_FullyShadedWithCelPS.Bind();
//		}
//		else
//		{
//			m_FullyShadedPS.Bind();
//		}
//		m_DepthMap.BindTexture(4);
//		m_ShadowBuffer.Set(&Details::s_ShadowInfo);
//		m_ShadowBuffer.BindToPixelShader(4);
//		break;
//		case Visualization::SomeSingleton::ShadingMode::DepthMapping:
//		m_MapDepthVS.Bind();
//		m_MapDepthPS.Bind();
//		m_TextureSampler.BindVertexShader(m_System, 0);
//		m_LightCamera.RenderPerspective();
//		break;
//		case Visualization::SomeSingleton::ShadingMode::Postprocessing:
//		m_PostProcessVS.Bind();
//		m_PostProcessPS.Bind();
//		m_TextureSampler.BindVertexShader(m_System, 0);
//		break;
//		default:
//		m_Mode = SomeSingleton::ShadingMode::None;
//		break;
//		}
//
//		m_LightingBuffer.BindToVertexShader(2);
//		m_LightingBuffer.BindToPixelShader(2);
//	}
//
//	void SomeSingletonImplementation::BindMaterial(const Material& p_Material)
//	{
//		Time("BindMaterial");
//
//		switch(m_Mode)
//		{
//		case Visualization::SomeSingleton::ShadingMode::Lit:
//		p_Material.BindLit(m_System);
//		break;
//		case Visualization::SomeSingleton::ShadingMode::Shading:
//		p_Material.BindShading(m_System);
//		break;
//		case Visualization::SomeSingleton::ShadingMode::LitShading:
//		p_Material.BindLitShading(m_System);
//		break;
//		case Visualization::SomeSingleton::ShadingMode::FullShading:
//		p_Material.BindFullShading(m_System);
//		if(CelShadingOn)
//		{
//			m_CelGradient.BindPixelShader(4);
//		}
//		break;
//		case Visualization::SomeSingleton::ShadingMode::DepthMapping:
//		p_Material.BindDepthMapping(m_System);
//		break;
//		case Visualization::SomeSingleton::ShadingMode::Postprocessing:
//		p_Material.BindShading(m_System);
//		m_PostProcessBuffer.Set(&Details::s_PostProcessInfo);
//		m_PostProcessBuffer.BindToPixelShader(0);
//		break;
//		default:
//		break;
//		}
//	}
//
//	void SomeSingletonImplementation::DrawSphere(const Mathematics::Matrix44& p_Transform)
//	{
//		Time("DrawingSphere");
//
//		switch(m_Mode)
//		{
//		case Visualization::SomeSingleton::ShadingMode::Lit:
//			{
//				Time("DrawingSimpleSphere");
//				m_LitSphere.Render(p_Transform);
//				break;
//			}
//		case Visualization::SomeSingleton::ShadingMode::Shading:
//		Halt("Cannot draw!");
//		break;
//		case Visualization::SomeSingleton::ShadingMode::LitShading:
//		Halt("Cannot draw!");
//		break;
//		case Visualization::SomeSingleton::ShadingMode::FullShading:
//			{
//				Time("DrawingFullShadingSphere");
//				m_FullyShadedSphere.Render(p_Transform);
//				break;
//			}
//		case Visualization::SomeSingleton::ShadingMode::DepthMapping:
//		m_FullyShadedSphere.Render(p_Transform);
//		break;
//		default:
//		break;
//		}
//	}
//
//	void SomeSingletonImplementation::DrawTorus(const Mathematics::Matrix44& p_Transform)
//	{
//		switch(m_Mode)
//		{
//		case Visualization::SomeSingleton::ShadingMode::Lit:
//		Halt("Cannot draw!");
//		break;
//		case Visualization::SomeSingleton::ShadingMode::Shading:
//		Halt("Cannot draw!");
//		break;
//		case Visualization::SomeSingleton::ShadingMode::LitShading:
//		Halt("Cannot draw!");
//		break;
//		case Visualization::SomeSingleton::ShadingMode::FullShading:
//		m_FullyShadedTorus.Render(p_Transform);
//		break;
//		case Visualization::SomeSingleton::ShadingMode::DepthMapping:
//		m_FullyShadedTorus.Render(p_Transform);
//		break;
//		default:
//		break;
//		}
//	}
//}
//
////===========================================================================
//// Interface
////===========================================================================
//
//
//void Visualization::SomeSingleton::Initialize(System& p_System, bool p_ShadowMapping)
//{
//	Assert(Details::s_Implementation == nullptr, "Already initialized!");
//
//	Details::s_Implementation = std::make_unique<SomeSingletonImplementation>(p_System);
//
//	Details::s_Implementation->Initialize();
//
//	Details::s_Implementation->ShadowsOn = p_ShadowMapping;
//	Details::s_Implementation->PostProcessingOn = true;
//
//	Details::s_DrawingScene = false;
//	Details::s_MappingDepth = false;
//}
//
//void Visualization::SomeSingleton::Terminate()
//{
//	Assert(Details::s_Implementation != nullptr, "Already terminated!");
//	Assert(!Details::s_DrawingScene, "Terminating while shading!");
//	Assert(!Details::s_MappingDepth, "Terminating while mapping depth!");
//
//	Details::s_Implementation->Terminate();
//
//	Details::s_Implementation.reset(nullptr);
//}
//
//void Visualization::SomeSingleton::SetShading(ShadingMode p_Mode)
//{
//	Assert(Details::s_DrawingScene, "Not drawing a scene!");
//	Details::s_Implementation->SetShading(p_Mode);
//}
//
//void Visualization::SomeSingleton::TogglePostProcess()
//{
//	Assert(!Details::s_DrawingScene, "Cannot toggle post process while drawing scene!");
//	Details::s_Implementation->PostProcessingOn 
//		= !Details::s_Implementation->PostProcessingOn;
//}
//
//void Visualization::SomeSingleton::ToggleCelShade()
//{
//	Assert(!Details::s_DrawingScene, "Cannot toggle cel shade while drawing scene!");
//	Details::s_Implementation->CelShadingOn 
//		= !Details::s_Implementation->CelShadingOn;
//}
//
//void Visualization::SomeSingleton::StartShadowMapping()
//{
//	Details::s_Implementation->StartDepthMapping();
//
//	SomeSingleton::StartScene(SomeSingleton::ShadingMode::DepthMapping);
//}
//
//void Visualization::SomeSingleton::EndShadowMapping()
//{
//	SomeSingleton::EndScene();
//
//	Details::s_Implementation->StopDepthMapping();
//}
//
//void Visualization::SomeSingleton::StartScene(ShadingMode p_Mode)
//{
//	Time("SceneRenderSetup");
//
//	Assert(!Details::s_DrawingScene, "Already shading!");
//	Assert(p_Mode != ShadingMode::Postprocessing, "Postprocess is special and can't be used here!");
//	
//	//postprocess target render
//	if(p_Mode != ShadingMode::DepthMapping
//		&& Details::s_Implementation->PostProcessingOn)
//	{
//		Details::s_Implementation->StartRenderMapping();
//	}
//
//	//depth mapping for shadows
//	if (Details::s_Implementation->ShadowsOn && p_Mode != ShadingMode::DepthMapping)
//	{
//		Details::s_Implementation->BindDepthMap();
//	}
//
//	Details::s_DrawingScene = true;
//	Details::s_Implementation->SetShading(p_Mode);
//}
//
//void Visualization::SomeSingleton::EndScene()
//{
//	Time("SceneRenderShutdown");
//
//	Details::s_Implementation->SetShading(ShadingMode::None);
//	Assert(Details::s_DrawingScene, "Not shading!");
//	Details::s_DrawingScene = false;
//	
//	if (Details::s_Implementation->ShadowsOn)
//	{
//		Details::s_Implementation->UnbindDepthMap();
//	}
//	
//	if (Details::s_Implementation->PostProcessingOn)
//	{
//		Details::s_Implementation->StopRenderMapping();
//	}
//}
//
//
//void Visualization::SomeSingleton::ShowLightDepth()
//{
//	Details::s_Implementation->LightDepthRender();
//}
//
//
//void Visualization::SomeSingleton::PostProcess()
//{
//	if (Details::s_Implementation->PostProcessingOn)
//	{
//		Details::s_Implementation->PostProcessRender();
//	}
//}
//
//PostProcessInfo& Visualization::SomeSingleton::PostProcessSettings()
//{
//	return Details::s_PostProcessInfo;
//}
//
//const Material& Visualization::SomeSingleton::DefaultMaterial()
//{
//	return Details::s_Implementation->DefaultMaterial();
//}
//
//void Visualization::SomeSingleton::RenderSphere(const Mathematics::Sphere3& p_Sphere
//	, const Mathematics::Quaternion& p_Orientation
//	, const Material& p_Material)
//{
//	Details::s_Implementation->BindMaterial(p_Material);
//	Details::s_Implementation->DrawSphere(MakeTranslation(p_Sphere.Centre) * MakeRotation(p_Orientation) * MakeScaling(p_Sphere.Radius * 2.0f));
//}
//
//void Visualization::SomeSingleton::RenderSphere(const Mathematics::Frame& p_Frame
//	, const f32 p_Radius, const Material& p_Material)
//{
//	Details::s_Implementation->BindMaterial(p_Material);
//	Details::s_Implementation->DrawSphere(p_Frame.GetLocalToWorld() * MakeScaling(p_Radius));
//}
//
//void Visualization::SomeSingleton::RenderTorus(const Mathematics::Frame& p_Frame
//	, const f32 p_Scale, const Material& p_Material)
//{
//	Details::s_Implementation->BindMaterial(p_Material);
//	Details::s_Implementation->DrawTorus(p_Frame.GetLocalToWorld() * MakeScaling(p_Scale));
//}