//===========================================================================
// Filename:	HelooTEXTUREWindowedApp.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "WindowedApp.h"
#include <Abstracts.h>
#include <Algorithms.h>

using namespace Visualization;
using namespace Mathematics;
using namespace Abstracts;
using namespace Algorithms;

//===========================================================================
// Class Definitions
//===========================================================================

WindowedApp::WindowedApp()
: Core::Application()
, m_Viewport()
, m_Camera()
, m_GraphicSystem()
, m_Sphere(m_GraphicSystem)
, m_Timer()
, m_Light()
, m_Texture()
, m_Sampler()
{}

//---------------------------------------------------------------------------

WindowedApp::~WindowedApp() {}

//---------------------------------------------------------------------------

void WindowedApp::OnInitialize(u32 p_Width, u32 p_Height)
{
	m_Viewport.Initialize(GetInstance(), GetAppName(), p_Width, p_Height, &WindowedApp::HandleMessages);

	HookupWindow(m_Viewport.GetWindowHandle());

	//Direct3D
	m_GraphicSystem.Initialize(m_Viewport.GetWindowHandle(), false);
	
	MeshBuilder::CreateSphere(m_Sphere.Mesh, Sphere(Point(0.0f, 0.0f, 0.0f), 1.0f));

	Material mat = Material(ConstantColours::White, ConstantColours::White, ConstantColours::White);

	m_Sphere.Initialize(mat);

	m_Timer.Initialize();

	m_Texture.Initialize(m_GraphicSystem, L"../Data/Images/Earth.jpg");

	m_Sampler.Initialize(m_GraphicSystem, Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	m_Light.Position = Vector(0.0f, 2.0f, 0.0f);
	m_Light.Ambient = ConstantColours::White;
	m_Light.Diffuse = ConstantColours::White;
	m_Light.Specular = ConstantColours::White;

}

//---------------------------------------------------------------------------

void WindowedApp::OnTerminate()
{
	m_Sampler.Terminate();

	m_Texture.Terminate();

	m_Sphere.Terminate();

	//Direct3D
	m_GraphicSystem.Terminate();

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

	m_Timer.Update();

	//direct3D
	m_GraphicSystem.BeginRender();

	//rendering
	ID3D11DeviceContext* context = m_GraphicSystem.GetContext();

	f32 t = m_Timer.GetTotalTime();
	
	m_Texture.BindPixelShader(m_GraphicSystem, 0);
	m_Sampler.BindPixelShader(m_GraphicSystem, 0);

	//get matrices
	TransformData data;

	data.MatWorld = RotationAboutZ(t) * RotationAboutX(ConstantScalars::PiOverTwo) * Translation(Vector(0.0f, 0.0f, 1.0f));


	//view matrix
	Point Position(0.0f, 0.0f, 3.0f);
	Point Focus(0.0f, 0.0f, 0.0f);

	data.MatView = ViewLookAt_LH(Position, Focus).Transpose();
	
	//projection
	data.MatProjection = PerspectiveProjection_LH(ConstantScalars::PiOverTwo, 1024.0f / 768.0f, 100.0f, 0.01f).Transpose();

	LightingData lights;

	lights.ViewPosition = Vector(3.0f, 0.0f, 0.0f);
	lights.LightDirection = m_Light.Position;

	lights.LightAmbient = m_Light.Ambient;
	lights.LightDiffuse = m_Light.Diffuse;
	lights.LightSpecular = m_Light.Specular;

	m_Sphere.Render(data, &lights);

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