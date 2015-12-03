#ifndef IncludedSyncWindowedAppH
#define IncludedSyncWindowedAppH

//===========================================================================
// Filename:	HelooTEXTWindowedApp.h
// Author:		Jarrod MacKay
// Description:	Provides a window to display visual application information.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Visualization.h>

namespace Synchronization
{
	//===========================================================================
	// Classes
	//===========================================================================

	class WindowedApp : public Core::Application
	{

		//Operators
	public:

		WindowedApp();

		virtual ~WindowedApp();

	//Methods
	protected:

		Visualization::System& GetGraphicsSystem();

		HWND GetWindowHandle() const;

	private:

		virtual void OnApplicationInitialize(u32 p_Width, u32 p_Height);

		virtual void OnApplicationTerminate();

		virtual void OnApplicationUpdate();

		virtual void OnInitialize() = 0;

		virtual void OnTerminate() = 0;

		virtual void OnUpdate(f32 p_DeltaTime) = 0;

		virtual void OnRender() = 0;

		static LRESULT WINAPI HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Attributes
	private:

		//system
		Core::Window m_Viewport;

		Visualization::System m_GraphicSystem;

		Core::Timer m_Timer;
	};
}

#endif //#ifndef IncludedSyncWindowedAppH