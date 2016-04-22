//===========================================================================
// Filename:	Test.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Test.h"

using namespace Visualization;
using namespace Mathematics;

namespace
{
	Frame originFrame;
	Frame testFrame;
	Quaternion cubeRotor;
	Vector3 testOffset;

	f32 sphereRadius = 4.0f;

	f32 ppTimer = 0.0f;

	FancyMaterial earthMaterial;

	Simulation::ParticleSystem<3> particleSystem;

	VerletParticle<3> earthParticle;

	bool viewThroughReflection = false;

	bool debugging = false;

	Gameplay::World gameWorld(4);
}

//===========================================================================
// Class Definitions
//===========================================================================

Test::Test()
	: Synchronization::Game()
	, m_Controller(GetInputSystem())
	, m_Camera()
	, m_Renderer(GetGraphicsSystem())
	, m_ParticleRenderer(GetGraphicsSystem())
	, m_WaterRenderer(GetGraphicsSystem())
	, m_PostProcessor(GetGraphicsSystem())
	, m_Terrain(GetGraphicsSystem())
	, m_Water(GetGraphicsSystem())
{}

//---------------------------------------------------------------------------

Test::~Test() {}

//---------------------------------------------------------------------------

void Test::OnInitialize()
{
	using namespace Mathematics;
	using namespace Visualization;
	using namespace ColourPallet;

	//scene
	m_Camera.Calibrate(MakeVector(0.0f, 10.0f, 33.0f), Zero3(), 1000.0f, PiOverTwo * 0.4f, true, 0.1f);

	//input
	m_Controller.Calibrate(&m_Camera.Transform);

	m_Renderer.Initialize();
	m_WaterRenderer.Initialize();
	m_ParticleRenderer.Initialize();
	m_PostProcessor.Initialize();

	Visualization::Light light;
	light.Position = MakeVector(-3.0f, -3.0f, -3.0f, Zero);
	light.Ambient = ColourPallet::Gray20;
	light.Diffuse = ColourPallet::White;
	m_Renderer.RegisterLight(light);
	m_WaterRenderer.RegisterLight(light);

	//test init
	testOffset = MakeVector(10.0f, 8.0f, 10.0f);
	testFrame.Translate(testOffset);

	//materials
	earthMaterial.Initialize(GetGraphicsSystem()
		, L"../Data/Images/earth_bump.jpg"
		, L"../Data/Images/earth_diffuse.jpg"
		, L"../Data/Images/earth_specular.jpg"
		, L"../Data/Images/earth_normal.jpg"
		, nullptr
		, L"../Data/Images/earth_umbral.jpg");
	earthMaterial.SetColours(10.0f
		, ColourPallet::Black
		, ColourPallet::Azure
		, ColourPallet::White);

	particleSystem.Initialize(0.5f);

	earthParticle = particleSystem.SpawnStaticParticle(Zero3());

	particleSystem.RandomSpawnSphere(10, Sphere3(Zero3(), sphereRadius), Zero3());

	gameWorld.Initialize();
	gameWorld.LoadLevel("../Data/Levels/test_level.xml");

	//water
	//waterFrame = originFrame;
	//Mesh<SurfaceVertex> waterMesh;
	//MeshBuilder::CreateHeightMesh(waterMesh, 256.0f, 128.0f);
	//m_Water.Initialize(waterMesh);
	//waterMesh.Destroy();

	////terrain
	//marsFrame = originFrame;
	//marsFrame.Translate(-2.0f * J());
	//Mesh<FramedVertex> terrainMesh;
	//MeshBuilder::CreateHeightMesh(terrainMesh, 256.0f, 128.0f);
	//m_Terrain.Initialize(terrainMesh);
	//terrainMesh.Destroy();

	//earthFrame = waterFrame;
	//earthFrame.Translate(5.0f * J());

	//sphereFrame = earthFrame;
}

//---------------------------------------------------------------------------

void Test::OnTerminate()
{
	earthMaterial.Terminate();
	//marsMaterial.Terminate();
	//moonMaterial.Terminate();

	m_Terrain.Terminate();
	m_Water.Terminate();

	gameWorld.Terminate();

	m_ParticleRenderer.Terminate();
	m_PostProcessor.Terminate();
	m_WaterRenderer.Terminate();
	m_Renderer.Terminate();
}

//---------------------------------------------------------------------------

void Test::OnUpdate(f32 p_DeltaTime)
{
	static f32 totalTime = 0.0f;
	totalTime += p_DeltaTime * 0.125f;
	f32 angle = p_DeltaTime * TwoPi * 0.0625f;
	originFrame.Yaw(angle);
	testFrame.Yaw(angle);
	//sphereFrame.SetPosition(MakeVector(sphereRadius * 2.0f * std::sin(2.0f * totalTime), sphereFrame.GetPosition()(1), sphereRadius * 2.0f * std::cos(2.0f * totalTime)));
	//sphereFrame.Yaw(angle * 0.5f);
	cubeRotor = Quaternion(originFrame.GetUp(), angle) * cubeRotor;
	cubeRotor.Normalize();
	
	particleSystem.Update(p_DeltaTime);

	//marsFrame.Yaw(-angle);
	//earthFrame.Yaw(angle);

	m_WaterRenderer.Update(totalTime);
}

void Test::OnInput(const f32 p_DeltaTime)
{
	using namespace Utilization;

	//first person
	m_Controller.Update(p_DeltaTime, GetGraphicsSystem().GetCentre());

	if (m_Controller.GetButton(Button::Quit))
	{
		m_Running = false;
		return;
	}

	if (m_Controller.GetButton(Button::FullScreen))
	{
		GetGraphicsSystem().ToggleFullscreen();
	}

	ppTimer -= p_DeltaTime;
	if (ppTimer < 0.0f)
	{
		if (m_Controller.GetButton(Button::PostProcessEffectDown))
		{
			m_PostProcessor.LastEffect();
			ppTimer = 0.5f;
		}
		if (m_Controller.GetButton(Button::PostProcessEffectUp))
		{
			m_PostProcessor.NextEffect();
			ppTimer = 0.5f;
		}
		//debug
		if(m_Controller.GetButton(Button::DebugScreen))
		{
			debugging = !debugging;
			if (debugging)
			{
				GetGraphicsSystem().ControlPanel.SetWireframe();
			}
			else
			{
				GetGraphicsSystem().ControlPanel.SetSolid();
			}
			ppTimer = 0.5f;
		}
		//if (m_Controller.GetButton(Button::))
		//{
		//	ppInfo.Intensity -= 0.1f;
		//}
		//if (m_Controller.GetButton(Button::PostProcessEffectUp))
		//{
		//	ppInfo.Intensity += 0.1f;
		//}
	}

	////edge detection
	//if(GetInputSystem().IsKeyDown(Utilization::Keys::F4))
	//{
	//	ppInfo.DetectEdges = !ppInfo.DetectEdges;
	//}
	//}
}

//---------------------------------------------------------------------------

void Test::OnRender()
{
	Time("GameRender");
	if(debugging)
	{
	Write(MakeVector(5.0f, 5.0f), "FPS = %4.4f, Effect = %s", GetFPS(), m_PostProcessor.GetEffectName());
	const Vector3 camPos = m_Camera.Transform.GetPosition();
	Write(MakeVector(5.0f, 25.0f), "CameraPos = %3.2f, %3.2f, %3.2f", camPos(0), camPos(1), camPos(2));
	Write(MakeVector(5.0f, 45.0f), "Camera = %s", (viewThroughReflection) ? ("Reflection") : ("Normal"));
	}

	gameWorld.Render();

	//m_PostProcessor.BindRenderTarget();
	//Camera reflectionCamera(m_Camera);/*
	//Plane3 reflectionPlane = Plane3(-J(), waterFrame.GetPosition());*/
	//const Vector3 pos = reflectionCamera.Transform.GetPosition();
	//const Vector3 left = reflectionCamera.Transform.GetLeft();/*
	//const Vector3 normal = reflectionPlane.Normal();*/
	//const Vector3 up = reflectionCamera.Transform.GetUp();
	//const Vector3 refFrwd = ReflectedVector(normal, reflectionCamera.Transform.GetForward());

	//reflectionCamera.Transform.SetPosition(
	//	-2.0f * reflectionPlane.SignedDistanceTo(pos) * normal + pos);
	//reflectionCamera.Transform.SetOrientation(refFrwd, ReflectedVector(normal, reflectionCamera.Transform.GetUp()));

	//reflection render
	//m_WaterRenderer.StartReflectionMapping(reflectionCamera);
	//m_Renderer.StartRenderingPersp(reflectionCamera);
	//{
	//	Time("RenderTwinSpheres");
	//	m_Renderer.SwitchShading(Renderer<FramedVertex>::Shading::Fancy);

	//	m_Renderer.RenderSphere(sphereFrame, sphereRadius * 0.5f);

	//	m_Renderer.BindMaterial(earthMaterial);

	//	m_Renderer.RenderSphere(Sphere3(earthFrame.GetPosition(), sphereRadius), Mathematics::IdentityRotor());
	//}
	//m_Renderer.StopRendering();
	//m_WaterRenderer.StopReflectionMapping();

	//normal render
	m_Renderer.StartRenderingPersp(m_Camera);
	{
		Time("RenderTwinSpheres");
		m_Renderer.SwitchShading(Renderer<FramedVertex>::Shading::Fancy);

		//m_Renderer.BindMaterial(moonMaterial);

		//m_Renderer.RenderTorus(sphereFrame, sphereRadius * 0.5f);

		m_Renderer.BindMaterial(earthMaterial);

		m_Renderer.RenderSphere(Sphere3(earthParticle.Position, sphereRadius), IdentityRotor());

		//m_Renderer.BindMaterial(marsMaterial);

		//m_Renderer.RenderSphere(marsFrame, sphereRadius);

		//m_Renderer.RenderModel(marsFrame, m_Terrain);
	}
	m_Renderer.StopRendering();

	m_ParticleRenderer.StartRendering(m_Camera);
	{
		Time("RenderParticles");
		for(auto particle : particleSystem.GetParticles())
		{
			m_ParticleRenderer.RenderSphere(Sphere3(particle.Position, particleSystem.GetParticleRadius()));
		}
	}
	m_ParticleRenderer.StopRendering();

	//m_WaterRenderer.StartRendering(m_Camera);
	//m_WaterRenderer.RenderModel(waterFrame, m_Water);
	//m_WaterRenderer.StopRendering();

	if (debugging)
	{
		//Visualization::Draw::AddFrame(sphereFrame, 3.0f);
		//Visualization::Draw::AddFrame(earthFrame, 3.0f);
		//Visualization::Draw::AddFrame(reflectionCamera.Transform, 3.0f);
		//Visualization::Draw::AddFrame(m_Camera.Transform, 3.0f);
		//Visualization::Draw::AddFrame(waterFrame, 3.0f);
		Visualization::Draw::Render(m_Camera);
	}

	//m_PostProcessor.UnbindRenderTarget();

	//m_PostProcessor.Render();
}