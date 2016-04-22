//===========================================================================
// Filename:	GameplayDemo.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <iostream>
#include <Abstracts.h>
#include <Mathematics.h>
#include <Algorithms.h>
#include <Gameplay.h>
#include "GameplayDemo.h"

using namespace Gameplay;
using namespace Visualization;
using namespace Mathematics;
using namespace ColourPallet;

namespace
{

	//TODO need camera component
	//TODO need object component that can initialize render and has a transform
	//TODO NEED TERRAIN componenet 
	//and have MESH SECTORS for fast ray casting
	//need camera controller component
	//need to remove any direct use of camera
	//and we shoudl only ask gameplay world

	//camera controller component should set main camera in initialize
	//the main camera properties should be in level xml

	//NEED A MODEL COMPONENET!!!

	//meta system needs support for pointer and array!!

	Gameplay::World world(3);
}

//===========================================================================
// Class Definitions
//===========================================================================

GameplayDemo::GameplayDemo()
: Synchronization::Game()
, m_Controller(GetInputSystem())
, m_Camera()
, m_BallMat()
{}

//---------------------------------------------------------------------------

GameplayDemo::~GameplayDemo() {}

//---------------------------------------------------------------------------

void GameplayDemo::OnInitialize()
{
	//TODO should be a tool command line 

	const char* fileName = "../Data/Templates/test.xml";

	//TiXmlDocument doc;
	//if(!doc.LoadFile(fileName))
	//{
	//	Halt("File was not loaded!");
	//}
	//PrintNode(&doc, 0);


	//m_GameObjectHandle = m_GameObjectFactory.Create(fileName);


	//scene
	m_Camera.Calibrate(MakeVector(-8.0f, Unity, Zero), Zero3(), 1000.0f, PiOverTwo * 0.4f, true, 0.1f);
	//input
	m_Controller.Calibrate(&m_Camera.Transform);

	
	//physics
	m_BallMat.Initialize(GetGraphicsSystem());

	//gameplay
	world.LoadLevel("../Data/Levels/test_level.xml");
}

//---------------------------------------------------------------------------

void GameplayDemo::OnTerminate()
{
	m_BallMat.Terminate();
}

//---------------------------------------------------------------------------

void GameplayDemo::OnUpdate(const f32 p_DeltaTime)
{


	//gameplay
	world.Update(p_DeltaTime);
}

//---------------------------------------------------------------------------

void GameplayDemo::OnRender()
{	
	//scene render	
	//gameplay
	world.Render();
	
	//debug draw
	Visualization::Draw::AddCoordinateAxes();
	Visualization::Draw::AddCoordinatePlaneXZ();
	Visualization::Draw::Render(m_Camera);
}

//---------------------------------------------------------------------------

void GameplayDemo::OnInput(const f32 p_DeltaTime)
{
	using namespace Utilization;
	//input
	m_Controller.Update(p_DeltaTime, GetGraphicsSystem().GetCentre());

	if(m_Controller.GetButton(Button::Quit))
	{
		m_Running = false;
		return;
	}

	if(m_Controller.GetButton(Button::FullScreen))
	{
		GetGraphicsSystem().ToggleFullscreen();
	}
}