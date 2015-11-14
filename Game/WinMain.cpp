//===========================================================================
// Filename:	WinMain.cpp
// Author:		Jarrod MacKay
// Description:	Game application launcher.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "WindowedApp.h"

//===========================================================================
// Main
//===========================================================================

int WINAPI WinMain( HINSTANCE hInstance
				   ,  HINSTANCE hPrevInstance
				   ,  LPSTR     lpCmdLine
				   ,  int       nCmdShow)
{
	Mathematics::Random::Initialize();
	WindowedApp myApplication;
	myApplication.Initialize(hInstance, "JARROD", 1024, 768);

	while(myApplication.IsRunning())
	{
		myApplication.Update();
	}

	myApplication.Terminate();
	return 0;
}