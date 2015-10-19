#ifndef IncludedCoreWindowH
#define IncludedCoreWindowH

//===========================================================================
// Filename:	Window.h
// Author:		Jarrod MacKay
// Description:	Provides a window class for visual application output.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Types.h"

//===========================================================================
// Classes
//===========================================================================

namespace Core
{
	class Window
	{
	//Operators
	public:

		Window();
		~Window();

	//Methods
	public:

		bool Initialize(HINSTANCE p_Instance
					  , LPCSTR p_AppName
					  , u32 p_Width
					  , u32 p_Height
					  , WNDPROC handlerFunction = &Window::HandleMessages);

		void Terminate();

		bool CloseMessageReceived();

		HWND GetWindowHandle() const { return m_Window; }

	private:

		static LRESULT CALLBACK HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Attributes
	public:

		//module instance handle
		HINSTANCE m_Instance;

		//window handle
		HWND m_Window;

		//application name
		std::string m_AppName;
	};
} // namespace Core

#endif //#ifndef IncludedCoreWindowH