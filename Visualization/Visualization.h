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

#include "Common.h"
#include "LinearColour.h"
#include "System.h"
#include "Vertices.h"
#include "Mesh.h"
#include "Buffers.h"
#include "Shaders.h"
#include "MeshBuilder.h"
#include "ConstantBuffer.h"
#include "Solid.h"
#include "Material.h"
#include "Light.h"
#include "Sampler.h"
#include "Texture.h"

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

		static void Initialize(HWND p_HandleToWindow, s32 p_ScreenHeight, s32 p_ScreenWidth);

		static void AddSphere(const Mathematics::Sphere& p_Sphere, LinearColour p_Colour);

		static void AddPlane(const Mathematics::Plane& p_Plane, LinearColour p_Colour);

		static void AddLineSegment(const Mathematics::Point& p_Point1
			, const Mathematics::Point& p_Point2
			, LinearColour p_Colour);

		static void Canvas();

		static void Paint();

		static s32 CheckExposure();

		static void UpdatePalette();

		static void SwapBuffer();

	private:

		static void SetPixels(bool p_UseDoubleBuffer);

		static u8 PaletteValue(u32 n, u32 bit, u32 sft);

		static HPALETTE GetPalette();

		static void SetColour(const LinearColour& p_Colour);

	//Attributes
	private:

		static HWND s_Window;

		//GDI device context
		static HDC s_DeviceContext;

		static HGLRC s_RenderingContext;

		static HPALETTE s_Palette;

		static s32 s_Exposure;
		
		static PIXELFORMATDESCRIPTOR s_PixelDescriptor;

		static s32 s_WindowWidth;

		static s32 s_WindowHeight;

		static f32 s_AspectRatio;
	};
} // namespace Visualization

#endif //#ifndef IncludedVisualizationH