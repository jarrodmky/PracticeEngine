//===========================================================================
// Filename:	WindowedApp.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "WindowedApp.h"
#include <Visualization.h>

//===========================================================================
// Class Definitions
//===========================================================================

WindowedApp::WindowedApp()
: Core::Application()
, m_Viewport()
{}

//---------------------------------------------------------------------------

WindowedApp::~WindowedApp() {}

//---------------------------------------------------------------------------

void WindowedApp::OnInitialize(u32 p_Width, u32 p_Height)
{
	m_Viewport.Initialize(GetInstance(), GetAppName(), p_Width, p_Height, &WindowedApp::HandleMessages);

	HookupWindow(m_Viewport.GetWindowHandle());
}

//---------------------------------------------------------------------------

void WindowedApp::OnTerminate()
{
	UnhookWindow();

	m_Viewport.Terminate();
}

//---------------------------------------------------------------------------

void WindowedApp::OnUpdate()
{
	if(m_Viewport.CloseMessageReceived())
	{
		m_Running = false;
	}
}

//---------------------------------------------------------------------------

LRESULT CALLBACK WindowedApp::HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUERYNEWPALETTE:
	case WM_PALETTECHANGED:
		Visualization::Renderer::UpdatePalette();
		return DefWindowProc(hwnd, msg, wParam, lParam);
	case WM_CREATE:
		Visualization::Renderer::Initialize(hwnd);
		break;
	case WM_PAINT:
		Visualization::Renderer::Paint();
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