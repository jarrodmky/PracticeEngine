//===========================================================================
// Filename:	HelooTEXTUREWindowedApp.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Game.h"

using namespace Visualization;
using namespace Mathematics;

//===========================================================================
// Class Definitions
//===========================================================================

Game::Game()
: Synchronization::WindowedApp()
, m_InputSystem()
, m_Controller(m_InputSystem)
, m_Camera(GetGraphicsSystem())
, m_LightingBuffer(GetGraphicsSystem())
, m_Matrix()
, m_DepthTestDisable()
, m_DepthTestEnable()
, m_Skyshape(GetGraphicsSystem())
, m_SkyshapeMat(GetGraphicsSystem())
, m_Terrain(GetGraphicsSystem())
, m_TerrainMat(GetGraphicsSystem())
, m_moon(GetGraphicsSystem())
, m_moonMat(GetGraphicsSystem())
, m_moonBump()
, m_earth(GetGraphicsSystem())
, m_earthMat(GetGraphicsSystem())
, m_earthBump()
, m_mars(GetGraphicsSystem())
, m_marsMat(GetGraphicsSystem())
, m_marsBump()
, m_shadedVS(GetGraphicsSystem())
, m_shadedPS(GetGraphicsSystem())
, m_bumpedVS(GetGraphicsSystem())
, m_bumpedPS(GetGraphicsSystem())
{}

//---------------------------------------------------------------------------

Game::~Game() {}

//---------------------------------------------------------------------------

void Game::OnInitialize()
{
	using namespace Mathematics;
	using namespace Visualization;
	using namespace ColourPallet;

	Random::Initialize();
	DebugTest(
	Draw::Initialize(GetGraphicsSystem(), 100000);
	);
	//input
	m_InputSystem.Initialize(GetWindowHandle());
	m_Controller.Calibrate();

	//scene
	m_Camera.Initialize(MakeVector(-8.0f, Unity, Zero), MakeVector(-1.0f, 10.0f, -15.0f), 0.75f * PiOverTwo, 1000.0f, 0.01f);

	LightingBuffer lights;
	lights.LightDirection = MakeVector(-3.0f, 0.0f, 0.0f, Zero);
	lights.LightAmbient = White;
	lights.LightDiffuse = White;
	lights.LightSpecular = White;
	m_LightingBuffer.Allocate(&lights);
	

	m_DepthTestDisable.Initialize(GetGraphicsSystem(), DepthStencil::DepthTest::None);
	m_DepthTestEnable.Initialize(GetGraphicsSystem(), DepthStencil::DepthTest::Default);

	//objects
	//skybox mesh and material
	MaterialBuffer matData;
	matData.MaterialReflectance = 0.0f;
	matData.MaterialAmbient = White;
	matData.MaterialDiffuse = Black;
	matData.MaterialSpecular = Black;
	Mesh<ShadedVertex> shadedMeshData;
	Mesh<BumpedVertex> bumpedMeshData;
	MeshBuilder::CreateInvertedCube(shadedMeshData, MakeVector(0.0f, 0.0f, 0.0f), 1.0f);

	m_SkyshapeMat.Initialize(GetGraphicsSystem(), matData, L"../Data/Images/space.jpg");
	m_Skyshape.Initialize(shadedMeshData);
	shadedMeshData.Destroy();

	//planet mesh and material
	matData.MaterialReflectance = 2.5f;
	matData.MaterialAmbient = Mathematics::LinearColour(0.2f, 0.2f, 0.2f, 1.0f);
	matData.MaterialSpecular = White;
	MeshBuilder::CreateBumpedSphere(bumpedMeshData, Sphere(MakeVector(0.0f, 0.0f, 0.0f), 1.0f));

	//moon mesh and material
	matData.MaterialDiffuse = Mathematics::LinearColour(0.8f, 0.8f, 0.8f, 1.0f);

	m_moon.Initialize(bumpedMeshData);
	m_moonMat.Initialize(GetGraphicsSystem(), matData, L"../Data/Images/moonColour.jpg");
	m_moonBump.Initialize(GetGraphicsSystem(), L"../Data/Images/moonBump.jpg");
	
	//earth mesh and material
	matData.MaterialDiffuse = Mathematics::LinearColour(0.7f, 0.7f, 0.9f, 1.0f);

	m_earth.Initialize(bumpedMeshData);
	m_earthMat.Initialize(GetGraphicsSystem(), matData, L"../Data/Images/earthColour.jpg");
	m_earthBump.Initialize(GetGraphicsSystem(), L"../Data/Images/earthBump.jpg");

	//mars mesh and material
	matData.MaterialDiffuse = Mathematics::LinearColour(0.9f, 0.7f, 0.7f, 1.0f);

	m_mars.Initialize(bumpedMeshData);
	m_marsMat.Initialize(GetGraphicsSystem(), matData, L"../Data/Images/marsColour.jpg");
	m_marsBump.Initialize(GetGraphicsSystem(), L"../Data/Images/marsBump.jpg");
	bumpedMeshData.Destroy();

	//terrain mesh and material
	matData.MaterialDiffuse = Mathematics::LinearColour(0.6f, 0.6f, 0.6f, 1.0f);
	MeshBuilder::CreateHeightMesh(shadedMeshData, 60, 60);

	m_Terrain.Initialize(shadedMeshData);
	m_TerrainMat.Initialize(GetGraphicsSystem(), matData, L"../Data/Images/rockTexture.jpg");
	shadedMeshData.Destroy();

	m_Terrain.Transform.Pitch(Pi);

	m_earth.Transform.Pitch(Pi / 4.0f);
	m_earth.Transform.Translate(MakeVector(-4.0f, 40.0f, -60.0f));
	m_earth.Transform.Scale(3.0f);

	m_mars.Transform.Pitch(Pi / 2.0f);
	m_mars.Transform.Translate(MakeVector(-2.0f, 10.0f, -10.0f));
	m_mars.Transform.Scale(2.0f);

	m_moon.Transform.Translate(MakeVector(-0.0f, 5.0f, 0.0f));
	m_moon.Transform.Scale(0.5f);
	//m_Sphere.Transform.Yaw(ConstantScalars::Pi);
	//m_Sphere.Transform.Pitch(ConstantScalars::PiOverTwo);

	//shading
	m_shadedVS.Compile(L"../Data/Shaders/Lighting.fx", "VS", "vs_4_0");
	m_shadedPS.Compile(L"../Data/Shaders/Lighting.fx", "PS", "ps_4_0");
	m_bumpedVS.Compile(L"../Data/Shaders/LightBump.fx", "VS", "vs_4_0");
	m_bumpedPS.Compile(L"../Data/Shaders/LightBump.fx", "PS", "ps_4_0");
}

//---------------------------------------------------------------------------

void Game::OnTerminate()
{
	m_bumpedPS.Release();
	m_bumpedVS.Release();
	m_shadedPS.Release();
	m_shadedVS.Release();

	m_moon.Terminate();
	m_moonMat.Terminate();
	m_moonBump.Terminate();

	m_earth.Terminate();
	m_earthMat.Terminate();
	m_earthBump.Terminate();

	m_mars.Terminate();
	m_marsMat.Terminate();
	m_marsBump.Terminate();

	m_Terrain.Terminate();
	m_TerrainMat.Terminate();

	m_DepthTestDisable.Terminate();
	m_DepthTestEnable.Terminate();
	m_Skyshape.Terminate();
	m_SkyshapeMat.Terminate();

	m_LightingBuffer.Free();

	m_Camera.Terminate();

	//Direct3D
	m_InputSystem.Terminate();
	DebugTest(
		Visualization::Draw::Terminate();
	);
}

//---------------------------------------------------------------------------

void Game::OnUpdate(f32 p_DeltaTime)
{

	//input
	m_InputSystem.Update();
	m_Controller.Update();

	if(m_Controller.Denied())
	{
		m_Running = false;
	}
	if(m_Controller.Fullscreen())
	{
		GetGraphicsSystem().ToggleFullscreen();
	}

	f32 moveSpeed = 10.0f;
	f32 angleSpeed = 2.0f;

	f32 forwardDist = moveSpeed * p_DeltaTime * m_Controller.GetLeftVerticalAxis();
	f32 rollAngle = angleSpeed * p_DeltaTime * m_Controller.GetRightHorizontalAxis();
	f32 pitchAngle = angleSpeed * p_DeltaTime * m_Controller.GetRightVerticalAxis();
	f32 yawAngle = -angleSpeed * p_DeltaTime * m_Controller.GetLeftHorizontalAxis();

	if (!EquivalentToZero(forwardDist))
	{
		m_Camera.Transform.MoveForward(forwardDist);
	}
	if (!EquivalentToZero(rollAngle))
	{
		m_Camera.Transform.Roll(rollAngle);
	}
	if (!EquivalentToZero(pitchAngle))
	{
		m_Camera.Transform.Pitch(pitchAngle);
	}
	if (!EquivalentToZero(yawAngle))
	{
		m_Camera.Transform.Yaw(yawAngle);
	}

	m_Skyshape.Transform.SetPosition(m_Camera.Transform.GetPosition());

	//scene
	//m_Camera.Update(p_DeltaTime);

	//sphere
	m_moon.Transform.Roll(-0.3f * p_DeltaTime);
	m_earth.Transform.Roll(0.5f * p_DeltaTime);
	m_mars.Transform.Roll(-0.3f * p_DeltaTime);
}

//---------------------------------------------------------------------------

void Game::OnRender()
{	
	//scene render
	m_Camera.Render();

	////
	//render standard shading
	////
	m_shadedVS.Bind();
	m_shadedPS.Bind();

	m_LightingBuffer.BindToVertexShader(2);
	m_LightingBuffer.BindToPixelShader(2);

	//skybox
	m_SkyshapeMat.Bind(GetGraphicsSystem(), 0);
	m_DepthTestDisable.BindToOutput(GetGraphicsSystem(), 0);
	m_Skyshape.Render();
	m_DepthTestEnable.BindToOutput(GetGraphicsSystem(), 0);

	//render terrain
	m_TerrainMat.Bind(GetGraphicsSystem(), 0);
	m_Terrain.Render();
	
	////
	//render bump shading
	////
	m_bumpedVS.Bind();
	m_bumpedPS.Bind();

	//render earth
	m_Matrix.Push(m_earth.Transform.GetLocalToWorld());
	m_earthBump.BindPixelShader(GetGraphicsSystem(), 1);
	m_earthMat.Bind(GetGraphicsSystem(), 0);
	m_earth.Render(m_Matrix.GetResult());
	
	//render moon
	m_Matrix.Push(m_moon.Transform.GetLocalToWorld());
	m_moonBump.BindPixelShader(GetGraphicsSystem(), 1);
	m_moonMat.Bind(GetGraphicsSystem(), 0);
	m_moon.Render(m_Matrix.GetResult());
	m_Matrix.Pop();
	
	m_Matrix.Pop();

	//render mars
	m_Matrix.Push(m_mars.Transform.GetLocalToWorld());
	m_marsBump.BindPixelShader(GetGraphicsSystem(), 1);
	m_marsMat.Bind(GetGraphicsSystem(), 0);
	m_mars.Render(m_Matrix.GetResult());
	m_Matrix.Pop();

	//debug draw
	DebugTest(
	Visualization::Draw::AddFrame(m_Terrain.Transform, 2.0f);
	Visualization::Draw::AddFrame(m_moon.Transform, 2.0f);
	Visualization::Draw::AddFrame(m_mars.Transform, 2.0f);
	Visualization::Draw::AddFrame(m_earth.Transform, 2.0f);
	Visualization::Draw::AddFrame(m_Camera.Transform, 2.0f);
	//Visualization::Draw::AddCoordinateAxes();

	//for(u32 i = 0; i < m_Mesh.GetVertexCount(); ++i)
	//{
	//	ShadedVertex& v = m_Mesh.GetVertex(i);
	//	Visualization::Draw::AddVector(v.Normal, Point(v.Position), ConstantColours::HotPink);
	//}

	Visualization::Draw::Render(m_Camera);
	);
}