#ifndef IncludedVisualizationH
#define IncludedVisualizationH

//===========================================================================
// Filename:	Visualization.h
// Author:		Jarrod MacKay
// Description:	Main entry point to the graphics library.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>

//===========================================================================
// Definitions
//===========================================================================

namespace Visualization
{
	class Renderer
	{

	NonInstantiable(Renderer);

	//Methods
	public:

		static void Initialize(HWND p_HandleToWindow);

		static void Paint();

		static s32 CheckExposure();

		static void UpdatePalette();

	private:

		static void SwapBuffer();

		static void SetPixels(bool p_UseDoubleBuffer);

		static u8 PaletteValue(u32 n, u32 bit, u32 sft);

		static HPALETTE GetPalette();

	//Attributes
	private:

		static HWND hWindow;

		//GDI device context
		static HDC hDeviceContext;

		static HGLRC hRenderingContext;

		static HPALETTE hPalette;

		static s32 hExposure; 
		
		static PIXELFORMATDESCRIPTOR hPixelDescriptor;

	};
} // namespace Visualization

#endif //#ifndef IncludedVisualizationH