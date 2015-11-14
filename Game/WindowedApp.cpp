//===========================================================================
// Filename:	WindowedApp.cpp
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

const scalar kTileSize = 0.65f;
const Vector kOffset(kTileSize * 0.5f - 3.0f, kTileSize * 0.5f - 3.0f, 0.0f);
Grid grid;
SearchContext<Dijkstra> context;
std::vector<u32> path;

namespace
{
	//filter
	bool IsBlocked(u32 p_Start, u32 p_End)
	{
		u32 x = grid.GetX(p_End);
		u32 y = grid.GetY(p_End);
		//TODO: decide if end is traversable
		return true;
	}

	void ShowPath()
	{
		const Graph& graph = grid.GetGraph();
		Assert(path.size() > 0, "No path set!");
		for(u32 i = 0; i < path.size() - 1; ++i)
		{
			const Graph::Node& startNode = graph.GetNode(path[i]);
			const Graph::Node& endNode = graph.GetNode(path[i + 1]);
			u32 x0 = grid.GetX(startNode.GetIndex());
			u32 y0 = grid.GetY(startNode.GetIndex());
			u32 x1 = grid.GetX(endNode.GetIndex());
			u32 y1 = grid.GetY(endNode.GetIndex());

			Vector a(x0 * kTileSize, y0 * kTileSize);
			Vector b(x1 * kTileSize, y1 * kTileSize);

			Renderer::AddLineSegment(Point(a + kOffset), Point(b + kOffset), ConstantColours::Green);
		}
	}

	void ShowNeighbours()
	{
		const Graph& graph = grid.GetGraph();
		for(u32 i = 0; i < graph.GetNumberOfNodes(); ++i)
		{
			const Graph::Node& node = graph.GetNode(i);
			u32 x0 = grid.GetX(node.GetIndex());
			u32 y0 = grid.GetY(node.GetIndex());
			
			for(u32 n = 0; n < node.GetNumberOfNeighbours(); ++n)
			{
				const Graph::Node& neighbour = node.GetNeighbour(n);
				u32 x1 = grid.GetX(neighbour.GetIndex());
				u32 y1 = grid.GetY(neighbour.GetIndex());

				Vector a(x0 * kTileSize, y0 * kTileSize);
				Vector b(x1 * kTileSize, y1 * kTileSize);

				Renderer::AddLineSegment(Point(a + kOffset), Point(b + kOffset), ConstantColours::Blue);
			}
		}
	}

	void ShowClosedList()
	{
		const Graph& graph = grid.GetGraph();
		for(u32 i = 0; i < context.ClosedList.size(); ++i)
		{
			const Graph::Node& startNode = graph.GetNode(context.ClosedList[i]);
			u32 next = context.Parents[startNode.GetIndex()];
			if (next == -1)
			{
				continue;
			}
			const Graph::Node& endNode = graph.GetNode(next);
			u32 x0 = grid.GetX(startNode.GetIndex());
			u32 y0 = grid.GetY(startNode.GetIndex());
			u32 x1 = grid.GetX(endNode.GetIndex());
			u32 y1 = grid.GetY(endNode.GetIndex());

			Vector a(x0 * kTileSize, y0 * kTileSize);
			Vector b(x1 * kTileSize, y1 * kTileSize);

			Renderer::AddLineSegment(Point(a + kOffset), Point(b + kOffset), ConstantColours::Red);
		}
	}
}



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

	//OpenGL
	Renderer::Initialize(m_Viewport.GetWindowHandle(), p_Height, p_Width);


	//AI
	grid.Initialize(10, 10);
	context.Filter = IsBlocked;

	const Graph& graph = grid.GetGraph();
	u32 numNodes = graph.GetNumberOfNodes();
	u32 start = Random::GetInteger(0, numNodes - 1);
	u32 end = 0;
	do
	{
		end = Random::GetInteger(0, numNodes - 1);
	} while (end == start);

	context.Initialize(numNodes, start, end);
	context.GetH = [](u32 p_Index1, u32 p_Index2)->f32
	{ return Vector(Point(static_cast<scalar>(grid.GetX(p_Index1)), static_cast<scalar>(grid.GetY(p_Index1)), 0.0f) 
				  - Point(static_cast<scalar>(grid.GetX(p_Index1)), static_cast<scalar>(grid.GetY(p_Index1)), 0.0f)).Length(); };
	context.GetG = [](u32 p_Index1, u32 p_Index2)->f32
	{ return Vector(Point(static_cast<scalar>(grid.GetX(p_Index1)), static_cast<scalar>(grid.GetY(p_Index1)), 0.0f) 
				  - Point(static_cast<scalar>(grid.GetX(p_Index1)), static_cast<scalar>(grid.GetY(p_Index1)), 0.0f)).Length(); };

	GraphSearch<Dijkstra>::Run(graph, context);
	GraphSearch<Dijkstra>::GetPath(context, path);
}

//---------------------------------------------------------------------------

void WindowedApp::OnTerminate()
{
	grid.Free();

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
	
	//OpenGL
	Renderer::Canvas();
	//Renderer::AddSphere(Sphere(0.0, 0.0, 0.0, 1.0), 0.0, 0.0, 0.0);
	//Renderer::AddSphere(Sphere(3.0, 0.0, 0.0, 0.5), 1.0, 0.0, 0.0);
	//Renderer::AddSphere(Sphere(0.0, 3.0, 0.0, 1.0), 0.0, 1.0, 0.0);
	//Renderer::AddSphere(Sphere(0.0, 0.0, 3.0, 2.0), 0.0, 0.0, 1.0);
	//Renderer::AddSphere(Sphere(0.0, -3.0, 0.0, 1.0), 1.0, 1.0, 0.0);
	//Renderer::AddSphere(Sphere(-3.0, 0.0, 0.0, 0.5), 1.0, 0.0, 1.0);
	//Renderer::AddSphere(Sphere(0.0, 0.0, -3.0, 2.0), 0.0, 1.0, 1.0);

	ShowPath();
	ShowClosedList();
	ShowNeighbours();

	Renderer::Paint();
	Renderer::SwapBuffer();
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