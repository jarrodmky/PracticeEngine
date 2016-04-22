#ifndef IncludedSyncGameH
#define IncludedSyncGameH

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
#include <Utilization.h>

namespace Synchronization
{
	//===========================================================================
	// Classes
	//===========================================================================

	class Game : public Core::Application
	{

		//Operators
	public:

		Game();

		virtual ~Game();

		//Methods
	protected:

		Visualization::System& GetGraphicsSystem();

		Utilization::System& GetInputSystem();

		f32 GetFPS() const;

		template<typename... t_Args>
		void Write(Mathematics::Vector2 p_Position, const char* p_String, const t_Args&... p_Args);

		HWND GetWindowHandle() const;

	private:

		virtual void OnApplicationInitialize(u32 p_Width, u32 p_Height);

		virtual void OnApplicationTerminate();

		virtual void OnApplicationUpdate();

		virtual void OnInitialize() = 0;

		virtual void OnTerminate() = 0;

		virtual void OnUpdate(const f32 p_DeltaTime) = 0;

		virtual void OnRender() = 0;

		virtual void OnInput(const f32 p_DeltaTime) = 0;

		static LRESULT WINAPI HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		//Attributes
	private:

		//system
		Core::Timer m_Timer;

		Core::Window m_Viewport;

		//graphics
		Visualization::System m_GraphicSystem;

		//mesh renderer and manger?
		//sprite renderer and manager? 

		//fonts
		Visualization::Spriter m_Spriter;
		Visualization::Font m_Arial16;

		//input
		Utilization::System m_InputSystem;
	};

	template<typename... t_Args>
	void Game::Write(Mathematics::Vector2 p_Position, const char* p_String, const t_Args&... p_Args)
	{
		char buffer[256];
		sprintf_s(buffer, 256, p_String, p_Args...);
		m_Arial16.QueueRender(buffer, p_Position);

	}
}

#endif //#ifndef IncludedSyncGameH