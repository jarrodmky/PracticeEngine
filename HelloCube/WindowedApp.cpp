//===========================================================================
// Filename:	HelooCubeWindowedApp.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "WindowedApp.h"
#include <Abstracts.h>
#include <Algorithms.h>
#include <Visualization.h>

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
, m_GraphicSystem()
, m_Mesh(m_GraphicSystem)
, m_Timer()
, m_Light()
, m_Material()
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
	
	//MeshBuilder<decltype(m_Mesh.Mesh)>::CreateCube(m_Mesh.Mesh, Point(0.0f, 0.0f, 0.0f), 3.0f);
	MeshBuilder<decltype(m_Mesh.Mesh)>::CreateSphere(m_Mesh.Mesh, Sphere(Point(0.0f, 0.0f, 0.0f), 1.0f));

	m_Mesh.Initialize();

	m_Timer.Initialize();
}

//---------------------------------------------------------------------------

void WindowedApp::OnTerminate()
{
	m_Mesh.Terminate();

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



	//get matrices
	TransformData data;

	data.MatWorld = DirectX::XMMatrixRotationY(t) * DirectX::XMMatrixRotationZ(1.5f * t);

	//view matrix
	DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 1.0f, -0.0f, 0.0f);
	DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, -0.0f, 0.0f);
	data.MatView = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(Eye, At, Up));

	//projection
	data.MatProjection = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, 1024.0f / 768.0f, 0.01f, 100.0f));

	m_Mesh.Render(data);

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