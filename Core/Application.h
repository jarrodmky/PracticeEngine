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
#include "Timer.h"

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

		void Initialize(HINSTANCE p_Instance, LPCSTR p_AppName, u32 p_Width, u32 p_Height);

		void Terminate();

		void Update();

		bool IsRunning() const {return m_Running; }

	protected:

		HINSTANCE GetInstance() const { return m_Instance; }

		LPCSTR GetAppName() const {return m_AppName; }

	private:

		virtual void OnApplicationInitialize(u32 p_Width, u32 p_Height) = 0;

		virtual void OnApplicationTerminate() = 0;

		virtual void OnApplicationUpdate() = 0;

	//Attributes
	protected:

		bool m_Running;

	private:

		HINSTANCE m_Instance;

		HWND m_Window;

		LPCSTR m_AppName;
	};
} // namespace Core

#endif //#ifndef IncludedCoreApplicationH