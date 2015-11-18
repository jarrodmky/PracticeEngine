#ifndef IncludedWindowedAppH
#define IncludedWindowedAppH

//===========================================================================
// Filename:	HelooTriangleWindowedApp.h
// Author:		Jarrod MacKay
// Description:	Provides a window to display visual application information.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Visualization.h>
#include "Buffers.h"

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
private:

	virtual void OnInitialize(u32 p_Width, u32 p_Height);

	virtual void OnTerminate();

	virtual void OnUpdate();

	static LRESULT WINAPI HandleMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Attributes
protected:

	Core::Window m_Viewport;

	Visualization::System m_GraphicSystem;

	Visualization::Mesh<Visualization::BasicVertex> m_Mesh;
	
	Visualization::VertexBuffer<Visualization::BasicVertex> m_VertexBuffer;

	Visualization::IndexBuffer<u32> m_IndexBuffer;

	Visualization::VertexShader m_VertexShader;

	Visualization::PixelShader m_PixelShader;
};

#endif //#ifndef IncludedWindowedAppH