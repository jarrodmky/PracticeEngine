//===========================================================================
// Filename:	Application.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Application.h"
#include "ScopeTimer.h"
#include "Logger.h"

using namespace Core;

//===========================================================================
// Class Definitions
//===========================================================================

Application::Application()
: m_Running(true)
, m_Instance(nullptr)
, m_Window(nullptr)
, m_AppName()
{}

//---------------------------------------------------------------------------

Application::~Application() {}

//---------------------------------------------------------------------------

void Application::Initialize(HINSTANCE p_Instance, LPCSTR p_AppName, u32 p_Width, u32 p_Height)
{
	m_Instance = p_Instance;
	m_AppName = p_AppName;

	CoInitialize(nullptr);

	Logger::get().open();

	ScopeTimer::StaticInitialize();

	OnApplicationInitialize(p_Width, p_Height);
}

//---------------------------------------------------------------------------

void Application::Terminate()
{
	OnApplicationTerminate();
	
	ScopeTimer::StaticShutdown();

	Logger::get().close();

	CoUninitialize();
}

//---------------------------------------------------------------------------

void Application::Update()
{
	OnApplicationUpdate();
}