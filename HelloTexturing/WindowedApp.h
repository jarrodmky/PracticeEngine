#ifndef IncludedWindoweTEXTUREdAppH
#define IncludedWindoweTEXTUREdAppH

//===========================================================================
// Filename:	HelooTEXTWindowedApp.h
// Author:		Jarrod MacKay
// Description:	Provides a window to display visual application information.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Mathematics.h>
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

	Visualization::System m_GraphicSystem;

	Visualization::Solid m_Sphere1;

	Visualization::Solid m_Sphere2;

	Core::Timer m_Timer;

	Visualization::Light m_Light;

	Visualization::Material m_Material;

	Visualization::Texture m_Texture;

	Visualization::Sampler m_Sampler;
};

#endif //#ifndef IncludedWindowedAppH