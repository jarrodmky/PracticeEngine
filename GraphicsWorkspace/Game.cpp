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
, m_Mesh()
, m_Sphere(GetGraphicsSystem())
, m_LightingBuffer()
, m_VertexShader(GetGraphicsSystem())
, m_PixelShader(GetGraphicsSystem())
, m_MaterialBuffer()
, m_Texture()
, m_Sampler()
{}

//---------------------------------------------------------------------------

Game::~Game() {}

//---------------------------------------------------------------------------

void Game::OnInitialize()
{
	using namespace Visualization;
	using namespace ConstantColours;

	Random::Initialize();
	Draw::Initialize(GetGraphicsSystem(), 10000);

	//input
	m_InputSystem.Initialize(GetWindowHandle());

	//scene
	m_Camera.Initialize(Point(0.0f, 0.0f, 2.0f), Point(0.0f, 0.0f, 0.0f), 0.75f * ConstantScalars::PiOverTwo, 1000.0f, 0.01f);

	LightingBuffer lights;
	lights.LightDirection = Vector(3.0f, 0.0f, 0.0f);
	lights.LightAmbient = DarkGray;
	lights.LightDiffuse = Gray;
	lights.LightSpecular = LightGray;
	m_LightingBuffer.Initialize(GetGraphicsSystem(), lights);
	
	//objects
	//MeshBuilder::CreateSphere(m_Mesh, Sphere(Point(0.0f, 0.0f, 0.0f), 1.0f));
	MeshBuilder::CreateInvertedCube(m_Mesh, Point(0.0f, 0.0f, 0.0f), 1.0f);
	m_Sphere.Initialize(m_Mesh);
	m_Sphere.Transform.Yaw(ConstantScalars::PiOverTwo);
	m_Sphere.Transform.Pitch(ConstantScalars::PiOverTwo);


	//shading
	m_VertexShader.Compile(L"../Data/Shaders/Lighting.fx", "VS", "vs_5_0");
	m_PixelShader.Compile(L"../Data/Shaders/Lighting.fx", "PS", "ps_5_0");

	//material
	Pigment pg = Pigment(ConstantColours::DarkGray, ConstantColours::DarkGray, ConstantColours::Gray);
	MaterialBuffer mat;
	mat.MaterialAmbient = pg.Ambient;
	mat.MaterialDiffuse = pg.Diffuse;
	mat.MaterialSpecular = pg.Specular;
	m_MaterialBuffer.Initialize(GetGraphicsSystem(), mat);

	m_Texture.Initialize(GetGraphicsSystem(), L"../Data/Images/Earth.jpg");
	m_Sampler.Initialize(GetGraphicsSystem(), Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

//---------------------------------------------------------------------------

void Game::OnTerminate()
{
	m_Sampler.Terminate();
	m_Texture.Terminate();

	m_MaterialBuffer.Terminate();

	m_PixelShader.Release();
	m_VertexShader.Release();

	m_Sphere.Terminate();
	m_Mesh.Destroy();

	m_LightingBuffer.Terminate();

	m_Camera.Terminate();

	//Direct3D
	m_InputSystem.Terminate();

	Visualization::Draw::Terminate();
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

	f32 moveSpeed = 1.0f;
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


	//scene
	//m_Camera.Update(p_DeltaTime);

	//sphere
	m_Sphere.Transform.Roll(p_DeltaTime);
	m_Sphere.Transform.Yaw(p_DeltaTime);
}

//---------------------------------------------------------------------------

void Game::OnRender()
{	
	//scene render
	m_Camera.Render();

	m_VertexShader.Bind();
	m_PixelShader.Bind();

	m_Texture.BindPixelShader(GetGraphicsSystem(), 0);
	m_Sampler.BindPixelShader(GetGraphicsSystem(), 0);

	m_LightingBuffer.BindVS(GetGraphicsSystem(), 2);
	m_LightingBuffer.BindPS(GetGraphicsSystem(), 2);
	m_MaterialBuffer.BindPS(GetGraphicsSystem(), 3);

	//render sphere
	m_Sphere.Render();

	//debug draw
	Visualization::Draw::AddFrame(m_Sphere.Transform, 2.0f);
	Visualization::Draw::AddFrame(m_Camera.Transform, 2.0f);
	//Visualization::Draw::AddCoordinateAxes();

	//for(u32 i = 0; i < m_Mesh.GetVertexCount(); ++i)
	//{
	//	ShadedVertex& v = m_Mesh.GetVertex(i);
	//	Visualization::Draw::AddVector(v.Normal, Point(v.Position), ConstantColours::HotPink);
	//}

	Visualization::Draw::Render(m_Camera);
}