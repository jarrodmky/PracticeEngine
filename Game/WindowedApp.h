#ifndef IncludedWindowedAppH
#define IncludedWindowedAppH

//===========================================================================
// Filename:	WindowedApp.h
// Author:		Jarrod MacKay
// Description:	Provides a window to display visual application information.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Visualization.h>

//===========================================================================
// Classes
//===========================================================================

class WindowedApp : public Core::Application 
{
//Operators
public:

	WindowedApp();

	virtual ~WindowedApp();

//Methods
private:

	virtual void OnInitialize(u32 p_Width, u32 p_Height);

	virtual void OnTerminate();

	virtual void OnUpdate();

	static LRESULT WINAPI HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Attributes
protected:

	Core::Window m_Viewport;

};

#endif //#ifndef IncludedWindowedAppH