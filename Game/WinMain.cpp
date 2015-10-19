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

int CALLBACK WinMain(_In_ HINSTANCE hInstance
				   , _In_ HINSTANCE hPrevInstance
				   , _In_ LPSTR     lpCmdLine
				   , _In_ int       nCmdShow)
{
	WindowedApp myApplication;
	myApplication.Initialize(hInstance, "MY GAME!!!", 1024, 768);

	while(myApplication.IsRunning())
	{
		myApplication.Update();
	}

	myApplication.Terminate();
	return 0;
}