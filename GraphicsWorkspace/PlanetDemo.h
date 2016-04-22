#ifndef IncludedPlanetDemoH
#define IncludedPlanetDemoH

//===========================================================================
// Filename:	PlanetDemo.h
// Author:		Jarrod MacKay
// Description:	Entry functions into the game loop.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Abstracts.h>
#include <Mathematics.h>
#include <Algorithms.h>
#include <Utilization.h>
#include <Visualization.h>
#include <Synchronization.h>

//===========================================================================
// Classes
//===========================================================================

class PlanetDemo : public Synchronization::Game
{

//Operators
public:

	PlanetDemo();

	virtual ~PlanetDemo();

//Methods
private:

	virtual void OnInitialize();

	virtual void OnTerminate();

	virtual void OnUpdate(const f32 p_DeltaTime);

	virtual void OnRender();

	virtual void OnInput(const f32 p_DeltaTime);

//Attributes
private:

	//input
	Utilization::Controller m_Controller;

	///////
	//scene
	///////
	Visualization::Camera m_Camera;
	
	//skybox
	Visualization::Material m_SkyshapeMat;

	//duck
	Visualization::MeshModel<Visualization::FramedVertex> m_Duck;
	Visualization::Material m_DuckMat;

	//terrain
	Visualization::SolidModel<Visualization::FramedMesh> m_Terrain;
	Visualization::Material m_TerrainMat;

	//earth
	Visualization::Material m_earthMat;

	//mars
	Visualization::Material m_marsMat;

	//moon
	Visualization::Material m_moonMat;

	//donut
	Visualization::Material m_donutMat;

	//test quad
	Visualization::SolidModel<Visualization::FramedMesh> m_TestQuad;

};

#endif //#ifndef IncludedPlanetDemoH