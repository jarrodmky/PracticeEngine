//===========================================================================
// Filename:	Application.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Application.h"

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

	OnApplicationInitialize(p_Width, p_Height);
}

//---------------------------------------------------------------------------

void Application::Terminate()
{
	OnApplicationTerminate();

	CoUninitialize();
}

//---------------------------------------------------------------------------

void Application::Update()
{
	OnApplicationUpdate();
}