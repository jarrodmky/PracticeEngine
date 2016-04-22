//===========================================================================
// Filename:	WinMain.cpp
// Author:		Jarrod MacKay
// Description:	Game application launcher.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "GameplayDemo.h"
#include <Gameplay.h>

//===========================================================================
// Main
//===========================================================================

int WINAPI WinMain( HINSTANCE hInstance
				   ,  HINSTANCE hPrevInstance
				   ,  LPSTR     lpCmdLine
				   ,  int       nCmdShow)
{
	Gameplay::MetaRegistration();

	GameplayDemo gameplayDemo;
	gameplayDemo.Initialize(hInstance, "Gameplay demo", 1024, 768);

	while (gameplayDemo.IsRunning())
	{
		gameplayDemo.Update();
	}

	gameplayDemo.Terminate();
	return 0;
}