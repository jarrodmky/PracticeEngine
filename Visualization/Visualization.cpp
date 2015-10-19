//===========================================================================
// Filename:	Window.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Visualization.h"
#include <gl/gl.h>
#include <gl/glu.h>

using namespace Core; 
using namespace Visualization;

//===========================================================================
// Class Definitions
//===========================================================================

HWND Renderer::hWindow = nullptr;

HDC Renderer::hDeviceContext = nullptr;

HGLRC Renderer::hRenderingContext;

HPALETTE Renderer::hPalette;

s32 Renderer::hExposure;

PIXELFORMATDESCRIPTOR Renderer::hPixelDescriptor;

//---------------------------------------------------------------------------

void Renderer::Initialize(HWND p_HandleToWindow)
{
	hExposure = 0;
	hWindow = p_HandleToWindow;
	hDeviceContext = GetDC(hWindow);
	SetPixels(true);
	hRenderingContext = wglCreateContext(hDeviceContext);
	wglMakeCurrent(hDeviceContext, hRenderingContext);

	RECT rect;

	GetClientRect(hWindow, &rect);

	glClearColor(0.5f, 1.0F, 1.0F, 0.0F);
	glClearDepth(1.0F);
	glDisable(GL_DEPTH_TEST);

	glViewport(0, 0, rect.right, rect.bottom);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)rect.right - 1, (float)rect.bottom - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glPointSize(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3ub(0, 0, 0);
}

//---------------------------------------------------------------------------

void Renderer::Paint()
{
	wglMakeCurrent(hDeviceContext, hRenderingContext);
	hExposure = 1;
}

//---------------------------------------------------------------------------

s32 Renderer::CheckExposure()
{
	s32 ret(hExposure);
	hExposure = 0;
	return ret;
}

//---------------------------------------------------------------------------

void Renderer::UpdatePalette()
{
	if (hPalette != NULL)
	{
		SelectPalette(GetDC(hWindow), hPalette, FALSE);
		RealizePalette(GetDC(hWindow));
	}
}

//---------------------------------------------------------------------------

void Renderer::SwapBuffer()
{
	glFlush();
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers(hDeviceContext);
}

//---------------------------------------------------------------------------

void Renderer::SetPixels(bool p_UseDoubleBuffer)
{
	hPixelDescriptor =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if (p_UseDoubleBuffer != 0)
	{
		hPixelDescriptor.dwFlags |= PFD_DOUBLEBUFFER;
	}

	int pfm = ChoosePixelFormat(hDeviceContext, &hPixelDescriptor);
	if (pfm != 0)
	{
		if (SetPixelFormat(hDeviceContext, pfm, &hPixelDescriptor) != FALSE)
		{
			hPalette = GetPalette();
			SelectPalette(hDeviceContext, hPalette, FALSE);
			RealizePalette(hDeviceContext);
			return;
		}
	}
}

//---------------------------------------------------------------------------

u8 Renderer::PaletteValue(u32 n, u32 bit, u32 sft)
{
	u32 msk;
	n >>= sft;
	msk = (1 << bit) - 1;
	n &= msk;
	return (u8)(n * 255 / msk);
}

//---------------------------------------------------------------------------

HPALETTE Renderer::GetPalette()
{
	HPALETTE neo;
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE *lp;
	int n, i;

	n = GetPixelFormat(hDeviceContext);
	DescribePixelFormat(hDeviceContext, n, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE)
	{
		n = 1 << pfd.cColorBits;
		lp = (LOGPALETTE *)malloc(sizeof(LOGPALETTE) + n*sizeof(PALETTEENTRY));
		lp->palVersion = 0x300;
		lp->palNumEntries = n;
		for (i = 0; i<n; i++)
		{
			lp->palPalEntry[i].peRed = PaletteValue(i, pfd.cRedBits, pfd.cRedShift);
			lp->palPalEntry[i].peGreen = PaletteValue(i, pfd.cGreenBits, pfd.cGreenShift);
			lp->palPalEntry[i].peBlue = PaletteValue(i, pfd.cBlueBits, pfd.cBlueShift);
			lp->palPalEntry[i].peFlags = 0;
		}

		neo = CreatePalette(lp);
		free(lp);
		lp = nullptr;
		return neo;
	}
	return NULL;
}