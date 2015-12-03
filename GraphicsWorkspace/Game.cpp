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
, m_Timer()
, m_Mesh()
, m_Controller(m_InputSystem)
, m_Camera()
, m_Sphere(GetGraphicsSystem())
, m_Light()
, m_Texture()
, m_Sampler()
{}

//---------------------------------------------------------------------------

Game::~Game() {}

//---------------------------------------------------------------------------

void Game::OnInitialize()
{
	Random::Initialize();
	Visualization::Draw::Initialize(GetGraphicsSystem(), 10000);

	//direct input
	m_InputSystem.Initialize(GetWindowHandle());
	
	//build mesh
	MeshBuilder::CreateSphere(m_Mesh, Sphere(Point(0.0f, 0.0f, 0.0f), 1.0f));

	Material mat = Material(ConstantColours::White, ConstantColours::Blue, ConstantColours::LightGray);

	m_Camera.Initialize(Point(0.0f, 0.0f, 2.0f), Point(0.0f, 0.0f, 0.0f), 0.75f * ConstantScalars::PiOverTwo, 1000.0f, 0.01f);

	m_Sphere.Initialize(mat, m_Mesh);

	m_Timer.Initialize();

	//texturing
	m_Texture.Initialize(GetGraphicsSystem(), L"../Data/Images/Earth.jpg");
	m_Sampler.Initialize(GetGraphicsSystem(), Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	m_Texture.BindPixelShader(GetGraphicsSystem(), 0);
	m_Sampler.BindPixelShader(GetGraphicsSystem(), 0);

	//make light
	m_Light.Position = Vector(0.0f, 0.0f, -3.0f);
	m_Light.Ambient = ConstantColours::DarkGray;
	m_Light.Diffuse = ConstantColours::Gray;
	m_Light.Specular = ConstantColours::LightGray;
}

//---------------------------------------------------------------------------

void Game::OnTerminate()
{
	m_Sampler.Terminate();

	m_Texture.Terminate();

	m_Sphere.Terminate();

	m_Mesh.Destroy();

	//Direct3D
	m_InputSystem.Terminate();

	Visualization::Draw::Terminate();
}

//---------------------------------------------------------------------------

void Game::OnUpdate(f32 p_DeltaTime)
{
	//sphere
	m_Sphere.Transform.Roll(p_DeltaTime);

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
	f32 yawAngle = angleSpeed * p_DeltaTime * m_Controller.GetLeftHorizontalAxis();

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
}

//---------------------------------------------------------------------------

void Game::OnRender()
{

	//get matrices
	TransformBuffer transforms;
	transforms.LocalToWorld = m_Sphere.Transform.LocalToWorld().Transposition();

	transforms.WorldToViewToProjection = (m_Camera.GetPerspectiveTransform(GetGraphicsSystem()) 
										  * m_Camera.GetWorldToViewTransform()).Transposition();										

	//get lights
	LightingBuffer lights;

	lights.ViewPosition = m_Camera.Transform.GetPosition().PositionVector();
	lights.LightDirection = m_Light.Position;

	lights.LightAmbient = m_Light.Ambient;
	lights.LightDiffuse = m_Light.Diffuse;
	lights.LightSpecular = m_Light.Specular;

	//render sphere
	m_Sphere.Render(transforms, &lights);

	Visualization::Draw::AddFrame(m_Sphere.Transform, 2.0f);
	Visualization::Draw::AddFrame(m_Camera.Transform, 2.0f);
	//Visualization::Draw::AddCoordinateAxes();

	for(u32 i = 0; i < m_Mesh.GetVertexCount(); ++i)
	{
		ShadedVertex& v = m_Mesh.GetVertex(i);
		Visualization::Draw::AddVector(v.Normal, Point(v.Position), ConstantColours::HotPink);
	}

	Visualization::Draw::Render(m_Camera);
}