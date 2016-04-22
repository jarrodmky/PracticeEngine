//===========================================================================
// Filename:	PlanetDemo.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "PlanetDemo.h"

using namespace Visualization;
using namespace Mathematics;

//===========================================================================
// Class Definitions
//===========================================================================

//namespace
//{
//	Frame skyFrame;
//	Frame marsFrame;
//	Frame earthFrame;
//	Frame moonFrame;
//	Frame duckFrame;
//	Frame quadFrame;
//	Frame terrainFrame;
//
//	PointCloud3 duckPoints;
//	AABB3 duckBox;
//
//	Matrix44 ndcToUvTransform = MakeMatrix(0.5f, 0.0f, 0.0f, 0.0f
//										   , 0.0f, -0.5f, 0.0f, 0.0f
//										   , 0.0f, 0.0f, 1.0f, 0.0f
//										   , 0.5f, 0.5f, 0.0f, 1.0f);
//}
//
//PlanetDemo::PlanetDemo()
//: Synchronization::Game()
//, m_Controller(GetInputSystem())
//, m_Camera(GetGraphicsSystem())
//, m_SkyshapeMat(GetGraphicsSystem())
//, m_Effect(GetGraphicsSystem())
//, m_Duck(GetGraphicsSystem())
//, m_DuckMat(GetGraphicsSystem())
//, m_Terrain(GetGraphicsSystem())
//, m_TerrainMat(GetGraphicsSystem())
//, m_earthMat(GetGraphicsSystem())
//, m_marsMat(GetGraphicsSystem())
//, m_moonMat(GetGraphicsSystem())
//, m_donutMat(GetGraphicsSystem())
//, m_TestQuad(GetGraphicsSystem())
//{
//}
//
////---------------------------------------------------------------------------
//
//PlanetDemo::~PlanetDemo() {}
//
////---------------------------------------------------------------------------
//
//void PlanetDemo::OnInitialize()
//{
//	using namespace Mathematics;
//	using namespace Visualization;
//	using namespace ColourPallet;
//
//	//scene
//	m_Camera.Initialize(MakeVector(-10.0f, Unity, Zero), Zero3(), 1000.0f, PiOverTwo * 0.4f, true, 0.1f);
//
//	//input
//	m_Controller.Initialize(&m_Camera.Transform);
//
//	//objects
//	//skybox mesh and material
//	m_SkyshapeMat.Initialize(L"../Data/Images/space.jpg");
//	m_SkyshapeMat.SetMaterial(0.0f, Black, White, White, Black);
//
//
//	m_Effect.Create(1000, MakeVector(0.0f, -20.0f, 0.0f));
//	
//	//earth material
//	m_earthMat.Initialize(L"../Data/Images/earth_diffuse.jpg", L"../Data/Images/earth_spec.jpg"
//		, L"../Data/Images/earth_normal.jpg", L"../Data/Images/earth_bump.jpg");
//	m_earthMat.SetMaterial(Gray, White, White);
//
//
//	//mars material
//	m_marsMat.Initialize(L"../Data/Images/mars_diffuse.jpg", nullptr, L"../Data/Images/mars_normal.jpg", L"../Data/Images/mars_bump.jpg");
//	m_marsMat.SetMaterial(White, White, Flame);
//	
//	//moon  material
//	m_moonMat.Initialize(L"../Data/Images/moon_diffuse.jpg", nullptr, nullptr, L"../Data/Images/moon_bump.jpg");
//	m_moonMat.SetMaterial(10.0f, Black, White, White, White);
//
//	m_donutMat.Initialize(L"../Data/Images/donut.jpg");
//	m_donutMat.SetMaterial(3.0f, Black, Black, White, White);
//	
//	//terrain mesh and material
//	ShadedMesh shadedMeshData;
//	MeshBuilder::CreateHeightMesh(shadedMeshData, 60, 60);
//
//	m_Terrain.Initialize(shadedMeshData);
//	m_TerrainMat.Initialize(L"../Data/Images/rockTexture.jpg");
//	shadedMeshData.Destroy();
//
//	terrainFrame.MoveDown(-3.0f);
//
//	//positions
//	earthFrame.Translate(MakeVector(10.0f, 10.0f, 10.0f));
//	marsFrame.Translate(MakeVector(-2.0f, 10.0f, -10.0f));
//	moonFrame.Translate(MakeVector(14.0f, 6.0f, 6.0f) * 0.95f);
//
//	m_Duck.Initialize(GetGraphicsSystem(), "../Data/Models/duck.txt");
//	m_DuckMat.Initialize(L"../Data/Images/duck.jpg");
//
//	//TEST QUAD
//	FullyShadedMesh quadMesh;
//	MeshBuilder::CreateQuad(quadMesh, Quad3(K(), I()));
//	m_TestQuad.Initialize(quadMesh);
//	quadMesh.Destroy();
//
//	quadFrame.Translate(5.0f * I());
//
//	m_Duck.Points(duckPoints);
//	duckBox = MakeBoundingBox(duckPoints);
//}
//
////---------------------------------------------------------------------------
//
//void PlanetDemo::OnTerminate()
//{
//	m_TestQuad.Terminate();
//
//	m_DuckMat.Terminate();
//	m_Duck.Terminate();
//
//	m_earthMat.Terminate();
//	m_marsMat.Terminate();
//	m_moonMat.Terminate();
//	m_donutMat.Terminate();
//
//	m_Terrain.Terminate();
//	m_TerrainMat.Terminate();
//
//	m_Effect.Destroy();
//
//	m_SkyshapeMat.Terminate();
//
//	m_Camera.Terminate();
//}
//
////---------------------------------------------------------------------------
//
//void PlanetDemo::OnUpdate(f32 p_DeltaTime)
//{
//	//skyFrame.SetPosition(m_Camera.Transform.GetPosition());
//
//	//scene
//	//m_Camera.Update(p_DeltaTime);
//	//m_Effect.Update(p_DeltaTime);
//
//	//sphere
//	earthFrame.Roll(0.2f * p_DeltaTime);
//	marsFrame.Roll(-0.3f * p_DeltaTime);
//	moonFrame.Pitch(0.5f * p_DeltaTime);
//	quadFrame.Rotate(J(), 0.1f * p_DeltaTime);
//}
//
////---------------------------------------------------------------------------
//
//void PlanetDemo::OnRender()
//{
//	Renderer::StartShadowMapping();
//
//	Renderer::RenderSphere(earthFrame, 3.0f, m_earthMat);
//	Renderer::RenderSphere(moonFrame, 0.5f, m_moonMat);
//
//	Renderer::EndShadowMapping();
//
//
//	Renderer::StartScene(Renderer::ShadingMode::FullShading);
//	//scene render
//	m_Camera.RenderPerspective();
//
//	Write(MakeVector(3.0f, 3.0f), "FPS: %lf, %d", GetFPS(), Renderer::PostProcessSettings().EffectIndex);
//
//	//skybox
//	//Renderer::RenderInvertedCube(skyFrame, Unity, m_SkyshapeMat);
//
//	//render terrain
//	//m_TerrainMat.Bind(GetGraphicsSystem(), 0);
//	//m_Terrain.Render(m_Terrain.Transform.GetLocalToWorld());
//
//	//m_Effect.Render(m_Camera);
//
//	m_TestQuad.Render(quadFrame.GetLocalToWorld());
//
//	//render mars
//	Renderer::RenderSphere(marsFrame, 2.0f, m_marsMat);
//
//	//render earth
//	Renderer::RenderSphere(earthFrame, 7.0f, m_earthMat);
//
//	//render moon
//	Renderer::RenderSphere(moonFrame, 0.5f, m_moonMat);
//
//	Renderer::RenderTorus(moonFrame, 1.0f, m_donutMat);
//
//	//render duck
//	m_DuckMat.BindFullShading(GetGraphicsSystem());
//	m_Duck.Render(GetGraphicsSystem(), MakeTranslation(MakeVector(1.0f, 1.0f, 1.0f)));
//
//	//debug draw
//	DebugBlock(
//		Visualization::Draw::AddFrame(m_Effect.Transform, 2.0f);
//	Visualization::Draw::AddFrame(terrainFrame, 2.0f);
//	Visualization::Draw::AddFrame(marsFrame, 2.0f);
//	Visualization::Draw::AddFrame(earthFrame, 2.0f);
//	//Visualization::Draw::AddFrame(m_Camera.Transform, 2.0f);
//	Visualization::Draw::AddBox(duckBox, ColourPallet::Blue);
//	Visualization::Draw::AddCoordinateAxes();
//	Visualization::Draw::Render(m_Camera);
//	);
//
//	Renderer::EndScene();
//
//	//Renderer::PostProcess();
//	Renderer::ShowLightDepth();
//}
//
//void PlanetDemo::OnInput(const f32 p_DeltaTime)
//{
//	using namespace Utilization;
//
//	m_Controller.Update(p_DeltaTime, GetGraphicsSystem().GetCentre());
//
//	if(m_Controller.GetButton(Button::Quit))
//	{
//		m_Running = false;
//	}
//	if(m_Controller.GetButton(Button::FullScreen))
//	{
//		GetGraphicsSystem().ToggleFullscreen();
//	}
//
//	if (m_Controller.GetButton(Button::DebugScreen))
//	{
//		Renderer::TogglePostProcess();
//		Renderer::ToggleWireframe();
//	}
//
//	if(m_Controller.GetButton(Button::PostProcessEffectDown))
//	{
//		--(Renderer::PostProcessSettings().EffectIndex);
//	}
//
//	if(m_Controller.GetButton(Button::PostProcessEffectUp))
//	{
//		++(Renderer::PostProcessSettings().EffectIndex);
//	}
//
//	Renderer::PostProcessSettings().Intensity += 0.2f * m_Controller.GetAxis(Axis::PPEffectIntensity);
//
//	//cel shade
//	if(m_Controller.GetButton(Button::CelShade))
//	{
//		Renderer::ToggleCelShade();
//	}
//
//	//edge detection
//	if(m_Controller.GetButton(Button::EdgeDetect))
//	{
//		Renderer::PostProcessSettings().DetectEdges = !Renderer::PostProcessSettings().DetectEdges;
//	}
//}