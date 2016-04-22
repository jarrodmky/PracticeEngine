#ifndef IncludedParticlesDemoH
#define IncludedParticlesDemoH

//===========================================================================
// Filename:	ParticlesDemo.h
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

class ParticlesDemo : public Synchronization::Game
{

//Operators
public:

	ParticlesDemo();

	virtual ~ParticlesDemo();

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

	//particle effects
	Visualization::ParticleEffect m_Effect;

	//earth
	Visualization::Material m_earthMat;

};

#endif //#ifndef IncludedParticlesDemoH