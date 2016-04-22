//===========================================================================
// Filename:	HelooTEXTUREGame.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Game.h"

using namespace Synchronization;

//===========================================================================
// Class Definitions
//===========================================================================

Game::Game()
{}

//---------------------------------------------------------------------------

Game::~Game() {}

//---------------------------------------------------------------------------

Visualization::System& Game::GetGraphicsSystem()
{
	return m_GraphicSystem;
}

//---------------------------------------------------------------------------

Utilization::System& Game::GetInputSystem()
{
	return m_InputSystem;
}

//---------------------------------------------------------------------------

f32 Game::GetFPS() const
{
	return static_cast<f32>(m_Timer.GetFramesPerSecond());
}

//---------------------------------------------------------------------------

HWND Game::GetWindowHandle() const
{
	return m_Viewport.GetWindowHandle();
}

//---------------------------------------------------------------------------

void Game::OnApplicationInitialize(u32 p_Width, u32 p_Height)
{
	//window setup
	m_Viewport.Initialize(GetInstance(), GetAppName(), p_Width, p_Height, &Game::HandleMessages);
	ShowWindow(m_Viewport.GetWindowHandle(), true);
	UpdateWindow(GetWindowHandle());

	//Direct3D
	m_GraphicSystem.Initialize(m_Viewport.GetWindowHandle(), false);

	m_Spriter.Initialize(m_GraphicSystem);
	m_Arial16.Initialize(m_GraphicSystem, "../Data/Fonts/Arial_16.font");

	//game specific
	Mathematics::Random::Initialize();
		Visualization::Draw::Initialize(GetGraphicsSystem(), 100000);

	//timing
	m_Timer.Initialize();

	//input
	m_InputSystem.Initialize(GetWindowHandle());

	OnInitialize();
}

//---------------------------------------------------------------------------

void Game::OnApplicationTerminate()
{
	OnTerminate();
	//input
	m_InputSystem.Terminate();
	
	//game specific
	Visualization::Draw::Terminate();

	m_Arial16.Terminate();
	m_Spriter.Terminate();

	//Direct3D
	m_GraphicSystem.Terminate();

	//window
	m_Viewport.Terminate();
}

//---------------------------------------------------------------------------

void Game::OnApplicationUpdate()
{
	Time("OnApplicationUpdate");
	UpdateWindow(m_Viewport.GetWindowHandle());

	m_Timer.Update();

	if(m_Viewport.CloseMessageReceived())
	{
		m_Running = false;
		return;
	}

	m_InputSystem.Update();

	const f32 dTime = static_cast<f32>(m_Timer.GetElapsedTime());

	OnInput(dTime);
	{
		Time("OnUpdate");
		OnUpdate(dTime);
	}
	
	{
		Time("RenderingLoop");

		//RENDER LOOP
		m_GraphicSystem.BeginRender(Mathematics::ColourPallet::Gray20);

		OnRender();
		
		{
			Time("SpriteRender");

			m_Spriter.BeginRender();
			m_Arial16.Render(m_Spriter);
			m_Spriter.EndRender();
			GetGraphicsSystem().ControlPanel.TestDepth(true);
			GetGraphicsSystem().ControlPanel.Bind();
		}

		m_GraphicSystem.EndRender();
	}
}

//---------------------------------------------------------------------------

LRESULT CALLBACK Game::HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
		return DefWindowProcA(hwnd, msg, wParam, lParam);
	}
	return 1;
}