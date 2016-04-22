//===========================================================================
// Filename:	WinMain.cpp
// Author:		Jarrod MacKay
// Description:	Game application launcher.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "ParticlesDemo.h"


template <typename t_Game>
void GameLoop(HINSTANCE p_MSInstance, LPCSTR p_AppName)
{
	t_Game runningGame;
	runningGame.Initialize(p_MSInstance, "Particles!", 1024, 768);

	while (runningGame.IsRunning())
	{
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
	GameLoop<ParticlesDemo>(hInstance, "Planet Demonstration!");
	return 0;
}