#ifndef IncludedGameplayDemoH
#define IncludedGameplayDemoH

//===========================================================================
// Filename:	GameplayDemo.h
// Author:		Jarrod MacKay
// Description:	Entry functions into the GameplayDemo loop.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Utilization.h>
#include <Visualization.h>
#include <Synchronization.h>

//===========================================================================
// Classes
//===========================================================================

class GameplayDemo : public Synchronization::Game
{

//Operators
public:

	GameplayDemo();

	virtual ~GameplayDemo();

//Methods
private:

	virtual void OnInitialize();

	virtual void OnTerminate();

	virtual void OnUpdate(const f32 p_DeltaTime);

	virtual void OnRender();

	virtual void OnInput(const f32 p_DeltaTime);

//Attributes
private:

	//GameplayDemo
	Utilization::Controller m_Controller;

	///////
	//scene
	///////
	Visualization::Camera m_Camera;

	//ball
	Visualization::Material m_BallMat;
};

#endif //#ifndef IncludedGameplayDemoH