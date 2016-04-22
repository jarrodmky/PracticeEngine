//===========================================================================
// Filename:	WinMain.cpp
// Author:		Jarrod MacKay
// Description:	Game application launcher.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Gameplay.h>
#include "PlanetDemo.h"
#include "Test.h"


template <typename t_Game>
void GameLoop(HINSTANCE p_MSInstance, LPCSTR p_AppName)
{
	t_Game runningGame;
	runningGame.Initialize(p_MSInstance, "GRAPHICS TEST", 1024, 768);

	Gameplay::MetaRegistration();

	while (runningGame.IsRunning())
	{
		Time("TotalLoop");
		runningGame.Update();
	}

	runningGame.Terminate();
}


//===========================================================================
// Main
//===========================================================================

int WINAPI WinMain( HINSTANCE hInstance
				   ,  HINSTANCE hPrevInstance
				   ,  LPSTR     lpCmdLine
				   ,  int       nCmdShow)
{
	//GameLoop<PlanetDemo>(hInstance, "Planet Demonstration!");
	GameLoop<Test>(hInstance, "GRAPHICS TEST");
	return 0;
}