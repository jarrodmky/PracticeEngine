//===========================================================================
// Filename:	ParticlesDemo.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "ParticlesDemo.h"
#include <Core.h>
#include <Simulation.h>

using namespace Visualization;
using namespace Mathematics;

//===========================================================================
// Class Definitions
//===========================================================================

namespace
{
	PointCloud3 duckPoints;
	AABB3 duckBox;

	Sphere3 earthSphere(Zero3(), 3.0f);
	//SphereReflector3 solidSphere(earthSphere);

	Matrix44 ndcToUvTransform = MakeMatrix(0.5f, 0.0f, 0.0f, 0.0f
										   , 0.0f, -0.5f, 0.0f, 0.0f
										   , 0.0f, 0.0f, 1.0f, 0.0f
										   , 0.5f, 0.5f, 0.0f, 1.0f);
}

ParticlesDemo::ParticlesDemo()
: Synchronization::Game()
, m_Controller(GetInputSystem())
, m_Camera(GetGraphicsSystem())
, m_SkyshapeMat(GetGraphicsSystem())
, m_Effect(GetGraphicsSystem())
, m_earthMat(GetGraphicsSystem())
{
}

//---------------------------------------------------------------------------

ParticlesDemo::~ParticlesDemo() {}

//---------------------------------------------------------------------------

void ParticlesDemo::OnInitialize()
{
	using namespace Mathematics;
	using namespace Visualization;
	using namespace ColourPallet;

	//scene
	m_Camera.Initialize(MakeVector(-10.0f, Unity, Zero), Zero3(), 1000.0f, PiOverTwo * 0.4f, true, 0.1f);

	//input
	m_Controller.Initialize(&m_Camera.Transform);

	//objects
	//skybox mesh and material
	m_SkyshapeMat.Initialize(L"../Data/Images/space.jpg");
	m_SkyshapeMat.SetMaterial(0.0f, Black, White, White, Black);


	m_Effect.Create(1000, MakeVector(0.0f, -20.0f, 0.0f));

	//earth material
	m_earthMat.Initialize(L"../Data/Images/earth_diffuse.jpg", L"../Data/Images/earth_spec.jpg"
						  , L"../Data/Images/earth_normal.jpg", L"../Data/Images/earth_bump.jpg");
	m_earthMat.SetMaterial(White, White, White);

	Simulation::Simulator::Initialize(42, -WorldUp(), 8.0f * WorldUp(), 3.0f);


}

//---------------------------------------------------------------------------

void ParticlesDemo::OnTerminate()
{
	m_earthMat.Terminate();

	m_Effect.Destroy();

	m_SkyshapeMat.Terminate();

	m_Camera.Terminate();
}

//---------------------------------------------------------------------------

void ParticlesDemo::OnUpdate(f32 p_DeltaTime)
{
	Time("UpdateLoop");
	//skyFrame.SetPosition(m_Camera.Transform.GetPosition());

	//scene
	//m_Camera.Update(p_DeltaTime);
	//m_Effect.Update(p_DeltaTime);

	Simulation::Simulator::Update(p_DeltaTime);

	//solidSphere.Operate(particleSet, particleRadius, p_DeltaTime);

	//sphere
	//earthFrame.Roll(0.2f * p_DeltaTime);
}

//---------------------------------------------------------------------------

void ParticlesDemo::OnRender()
{
	Time("RenderLoop");
	{
		Time("DepthMapping");
		Renderer::StartShadowMapping();

		Renderer::RenderSphere(earthSphere, IdentityRotor(), m_earthMat);

		Renderer::EndShadowMapping();
	}
	//scene render
	{
		Time("SceneRender");

		m_Camera.RenderPerspective();

		Write(MakeVector(3.0f, 3.0f), "FPS: %f, %d", GetFPS(), Renderer::PostProcessSettings().EffectIndex);

		//shading
		Renderer::StartScene(Renderer::ShadingMode::Lit);

		const scalar partRadius = Simulation::Simulator::GetParticleRadius();
		for(auto particle : Simulation::Simulator::GetParticles())
		{
			const Sphere3 shell(particle.Position, partRadius);
			Renderer::RenderSphere(shell, IdentityRotor());
		}

		Renderer::SetShading(Renderer::ShadingMode::FullShading);

		//render earth
		Renderer::RenderSphere(earthSphere, IdentityRotor(), m_earthMat);

		//render duck

		//debug draw
		DebugBlock(
			Visualization::Draw::AddFrame(m_Effect.Transform, 2.0f);
		//Visualization::Draw::AddFrame(earthFrame, 2.0f);
		//Visualization::Draw::AddFrame(m_Camera.Transform, 2.0f);
		Visualization::Draw::AddBox(duckBox, ColourPallet::Blue);
		Visualization::Draw::AddCoordinateAxes();
		Visualization::Draw::Render(m_Camera);
		);

		Renderer::EndScene();
	}
	{
		Time("PostProcess");
		Renderer::PostProcess();
	}
}

void ParticlesDemo::OnInput(const f32 p_DeltaTime)
{
	Time("InputLoop");
	using namespace Utilization;

	m_Controller.Update(p_DeltaTime, GetGraphicsSystem().GetCentre());

	if(m_Controller.GetButton(Button::Quit))
	{
		m_Running = false;
	}
	if(m_Controller.GetButton(Button::FullScreen))
	{
		GetGraphicsSystem().ToggleFullscreen();
	}

	if(m_Controller.GetButton(Button::DebugScreen))
	{
		Renderer::TogglePostProcess();
		Renderer::ToggleWireframe();
	}

	if(m_Controller.GetButton(Button::PostProcessEffectDown))
	{
		--(Renderer::PostProcessSettings().EffectIndex);
	}

	if(m_Controller.GetButton(Button::PostProcessEffectUp))
	{
		++(Renderer::PostProcessSettings().EffectIndex);
	}

	Renderer::PostProcessSettings().Intensity += 0.2f * m_Controller.GetAxis(Axis::PPEffectIntensity);

	//cel shade
	if(m_Controller.GetButton(Button::CelShade))
	{
		Renderer::ToggleCelShade();
	}

	//edge detection
	if(m_Controller.GetButton(Button::EdgeDetect))
	{
		Renderer::PostProcessSettings().DetectEdges = !Renderer::PostProcessSettings().DetectEdges;
	}
}