//===========================================================================
// Filename:	HelooTEXTUREWindowedApp.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "WindowedApp.h"

using namespace Visualization;
using namespace Synchronization;

//===========================================================================
// Class Definitions
//===========================================================================

WindowedApp::WindowedApp()
: Core::Application()
, m_Viewport()
, m_GraphicSystem()
, m_Timer()
{}

//---------------------------------------------------------------------------

WindowedApp::~WindowedApp() {}

//---------------------------------------------------------------------------

System& WindowedApp::GetGraphicsSystem()
{
	return m_GraphicSystem;
}

//---------------------------------------------------------------------------

HWND WindowedApp::GetWindowHandle() const
{
	return m_Viewport.GetWindowHandle();
}

//---------------------------------------------------------------------------

void WindowedApp::OnApplicationInitialize(u32 p_Width, u32 p_Height)
{
	m_Viewport.Initialize(GetInstance(), GetAppName(), p_Width, p_Height, &WindowedApp::HandleMessages);

	ShowWindow(m_Viewport.GetWindowHandle(), true);

	UpdateWindow(GetWindowHandle());

	//Direct3D
	m_GraphicSystem.Initialize(m_Viewport.GetWindowHandle(), false);

	m_Timer.Initialize();

	OnInitialize();
}

//---------------------------------------------------------------------------

void WindowedApp::OnApplicationTerminate()
{
	OnTerminate();

	//Direct3D
	m_GraphicSystem.Terminate();

	m_Viewport.Terminate();
}

//---------------------------------------------------------------------------

void WindowedApp::OnApplicationUpdate()
{
	UpdateWindow(m_Viewport.GetWindowHandle());

	m_Timer.Update();

	if(m_Viewport.CloseMessageReceived())
	{
		m_Running = false;
	}

	OnUpdate(m_Timer.GetElapsedTime());

	//RENDER LOOP
	m_GraphicSystem.BeginRender();

	OnRender();

	m_GraphicSystem.EndRender();
}

//---------------------------------------------------------------------------

LRESULT CALLBACK WindowedApp::HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUERYNEWPALETTE:
	case WM_PALETTECHANGED:
		//Renderer::UpdatePalette();
		return DefWindowProc(hwnd, msg, wParam, lParam);
	case WM_CLOSE:
		PostMessage(hwnd, msg, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 1;
}