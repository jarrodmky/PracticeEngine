//===========================================================================
// Filename:	HelooTriangleWindowedApp.cpp
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
, m_Mesh()
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

	m_Mesh.Allocate(3, 3);
	m_Mesh.GetVertex(0).Position = Vector(0.0f, 0.5f, 0.5f);
	m_Mesh.GetVertex(1).Position = Vector(0.5f, -0.5f, 0.5f);
	m_Mesh.GetVertex(2).Position = Vector(-0.5f, -0.5f, 0.5f);
	m_Mesh.GetVertex(0).Colour = ConstantColours::Chartreuse;
	m_Mesh.GetVertex(1).Colour = ConstantColours::Orange;
	m_Mesh.GetVertex(2).Colour = ConstantColours::Indigo;
	m_Mesh.GetIndex(0) = 0;
	m_Mesh.GetIndex(1) = 1;
	m_Mesh.GetIndex(2) = 2;

	//Vertex buffer
	m_VertexBuffer.Allocate(m_Mesh.GetVertices(), m_Mesh.GetVertexCount(), m_GraphicSystem.GetDevice());

	//index buffer
	m_IndexBuffer.Allocate(m_Mesh.GetIndices(), m_Mesh.GetIndexCount(),  m_GraphicSystem.GetDevice(), TriangleList);

	//vertex shader compile
	m_VertexShader.Compile(L"../Data/Shaders/DoSomething.fx", m_GraphicSystem.GetDevice());

	//pixel shader compile
	m_PixelShader.Compile(L"../Data/Shaders/DoSomething.fx", m_GraphicSystem.GetDevice());
}

//---------------------------------------------------------------------------

void WindowedApp::OnTerminate()
{
	m_PixelShader.Release();
	m_VertexShader.Release();
	m_IndexBuffer.Free();
	m_VertexBuffer.Free();;

	m_Mesh.Destroy();

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

	//direct3D
	m_GraphicSystem.BeginRender(ConstantColours::Aquamarine);

	//rendering
	ID3D11DeviceContext* context = m_GraphicSystem.GetContext();
	m_VertexShader.Bind(context);
	m_PixelShader.Bind(context);

	//set vertex buffer
	m_VertexBuffer.Bind(context);

	//set primitive topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_IndexBuffer.Bind(context);
	context->DrawIndexed(m_Mesh.GetIndexCount(), 0, 0);

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