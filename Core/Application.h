#ifndef IncludedCoreApplicationH
#define IncludedCoreApplicationH

//===========================================================================
// Filename:	Application.h
// Author:		Jarrod MacKay
// Description:	Provides a Application class for visual application output.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Common.h"
#include "Types.h"

//===========================================================================
// Classes
//===========================================================================

namespace Core
{
	class Application
	{
	//Operators
	public:

		Application();
		virtual ~Application();

	//Methods
	public:

		bool Initialize(HINSTANCE p_Instance, LPCSTR p_AppName, u32 p_Width, u32 p_Height);

		void Terminate();

		void HookupWindow(HWND p_Hwnd);

		void UnhookWindow();

		void Update();

		bool IsRunning() const {return m_Running; }

	protected:

		HINSTANCE GetInstance() const { return m_Instance; }

		HWND GetWindow() const {return m_Window; }

		const char* GetAppName() const {return m_AppName.c_str(); }

	private:

		virtual void OnInitialize(u32 p_Width, u32 p_Height) = 0;

		virtual void OnTerminate() = 0;

		virtual void OnUpdate() = 0;

	//Attributes
	protected:

		bool m_Running;

	private:

		HINSTANCE m_Instance;

		HWND m_Window;

		std::string m_AppName;
	};
} // namespace Core

#endif //#ifndef IncludedCoreApplicationH