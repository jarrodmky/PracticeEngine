#ifndef IncludedTestH
#define IncludedTestH

//===========================================================================
// Filename:	Test.h
// Author:		Jarrod MacKay
// Description:	Testing for graphics
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Abstracts.h>
#include <Meta.h>
#include <Mathematics.h>
#include <Algorithms.h>
#include <Utilization.h>
#include <Simulation.h>
#include <Visualization.h>
#include <Synchronization.h>
#include <Gameplay.h>

//===========================================================================
// Classes
//===========================================================================

class Test : public Synchronization::Game
{

//Operators
public:

	Test();

	virtual ~Test();

//Methods
private:

	virtual void OnInitialize();

	virtual void OnTerminate();

	virtual void OnUpdate(const f32 p_DeltaTime);

	virtual void OnRender();

	virtual void OnInput(const f32 p_DeltaTime);

	void DrawScene(const Visualization::Camera& p_Camera);

	void PostProcess();

//Attributes
private:

	//input
	Utilization::Controller m_Controller;

	//scene
	Visualization::Camera m_Camera;

	Visualization::FramedVertexRenderer m_Renderer;
	Visualization::LitRenderer m_ParticleRenderer;
	Visualization::WaterRenderer m_WaterRenderer;
	Visualization::PostProcessor m_PostProcessor;

	Visualization::SolidModel<Visualization::FramedVertex> m_Terrain;

	Visualization::SolidModel<Visualization::SurfaceVertex> m_Water;
};

#endif //#ifndef IncludedTestH