//===========================================================================
// Filename:	Window.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Window.h"
#include "Debug.h"

using namespace Core;

//===========================================================================
// Class Definitions
//===========================================================================

Window::Window()
: m_Instance(nullptr)
, m_Window(nullptr)
, m_AppName()
{}

//---------------------------------------------------------------------------

Window::~Window() {}

//---------------------------------------------------------------------------

bool Window::Initialize(HINSTANCE p_Instance, LPCSTR p_AppName, u32 p_Width, u32 p_Height, WNDPROC handlerFunction)
{
	m_Instance = p_Instance;
	m_AppName = p_AppName;

	//Register class
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = handlerFunction;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = p_Instance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = p_AppName;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	Verify(RegisterClassExA(&wcex), "[Window.cpp] Failed to register window class!");

	//Size window
	RECT rc = {0, 0, p_Width, p_Height};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	const s32 screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const s32 screenHeight = GetSystemMetrics(SM_CYSCREEN);
	const s32 winWidth = rc.right - rc.left;
	const s32 winHeight = rc.bottom - rc.top;
	const s32 left = (screenWidth - winWidth) >> 1;
	const s32 top = (screenHeight - winHeight) >> 1;

	//Create window object
	m_Window = CreateWindowA
	(
		p_AppName,
		p_AppName,
		WS_OVERLAPPEDWINDOW,
		left,
		top,
		winWidth,
		winHeight,
		nullptr,
		nullptr,
		p_Instance,
		nullptr
	);

	Assert(m_Window, "[Window.cpp] Failed to create window!");

	ShowWindow(m_Window, SW_SHOW);
	Verify(SetCursorPos(screenWidth >> 1, screenHeight >> 1), "[Window.cpp] Failed to set cursor position!");

	return true;
}

//---------------------------------------------------------------------------

void Window::Terminate()
{
	DestroyWindow(m_Window);

	UnregisterClassA(m_AppName, m_Instance);

	m_Window = nullptr;

	m_Instance = nullptr;
}

//---------------------------------------------------------------------------

bool Window::CloseMessageReceived()
{
	MSG msg = {0};

	if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (WM_CLOSE == msg.message);
}

//---------------------------------------------------------------------------

LRESULT CALLBACK Window::HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
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