#ifndef IncludedGameH
#define IncludedGameH

//===========================================================================
// Filename:	Game.h
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

class Game : public Synchronization::WindowedApp
{

//Operators
public:

	Game();

	virtual ~Game();

//Methods
private:

	virtual void OnInitialize();

	virtual void OnTerminate();

	virtual void OnUpdate(f32 p_DeltaTime);

	virtual void OnRender();

//Attributes
private:

	//game
	Utilization::System m_InputSystem;

	Core::Timer m_Timer;

	Utilization::InputState m_Controller;

	//scene
	Visualization::Camera m_Camera;

	Visualization::Mesh<Visualization::ShadedVertex> m_Mesh;

	Visualization::Solid m_Sphere;

	Visualization::Light m_Light;

	//material
	Visualization::Texture m_Texture;

	Visualization::Sampler m_Sampler;
};

#endif //#ifndef IncludedGameH