//===========================================================================
// Filename:	Window.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Visualization.h"
#include <GL/gl.h>
#include <GL/glu.h>

using namespace Core; 
using namespace Visualization;
using namespace Mathematics;

//===========================================================================
// Class Definitions
//===========================================================================

namespace
{
	u32 g_ShapeResolution = 150;
	GLuint g_SphereList = 0;

	void CompileSphere()
	{
		//g_SphereList = glGenLists(1);
		//glNewList(g_SphereList, GL_COMPILE);

		//u32 uRes = 2 * g_ShapeResolution + 1;
		//u32 vRes = g_ShapeResolution + 1;
		//scalar theta, phi;
		//scalar st, sp, ct, cp;

		//scalar deltaAngle = ConstantScalars::Pi / static_cast<scalar>(g_ShapeResolution);

		//for (u32 v = 0; v < vRes; ++v)
		//{
		//	glBegin(GL_TRIANGLE_STRIP);

		//	for (u32 u = 0; u < uRes; ++u)
		//	{
		//		theta = static_cast<scalar>(u)* deltaAngle;

		//		for (u32 k = 0; k < 2; ++k)
		//		{
		//			phi = static_cast<scalar>(v + k) * deltaAngle;

		//			st = sin(theta);
		//			sp = sin(phi);
		//			ct = cos(theta);
		//			cp = cos(phi);

		//			glVertex3f(ct * sp, st * sp, cp);
		//			glNormal3f(ct * sp, st * sp, cp);
		//		}
		//	}
		//	glEnd();
		//}
		//glEndList();
	}
}

HWND Renderer::s_Window = nullptr;

HDC Renderer::s_DeviceContext = nullptr;

HGLRC Renderer::s_RenderingContext = nullptr;

HPALETTE Renderer::s_Palette = nullptr;

s32 Renderer::s_Exposure = 0;

PIXELFORMATDESCRIPTOR Renderer::s_PixelDescriptor;

s32 Renderer::s_WindowWidth = 0;

s32 Renderer::s_WindowHeight = 0;

f32 Renderer::s_AspectRatio = 0.0;

GLdouble CameraMatrix[16] = 
	{
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0
	};

//---------------------------------------------------------------------------

void Renderer::Initialize(HWND p_HandleToWindow, s32 p_ScreenHeight, s32 p_ScreenWidth)
{
	//s_Exposure = 0;
	//s_Window = p_HandleToWindow;
	//s_DeviceContext = GetDC(s_Window);
	//s_WindowHeight = static_cast<GLsizei>(p_ScreenHeight);
	//s_WindowWidth = static_cast<GLsizei>(p_ScreenWidth);
	//f32 floatWidth = static_cast<f32>(s_WindowWidth);
	//f32 floatHeight = static_cast<f32>(s_WindowHeight);
	//s_AspectRatio = floatWidth / floatHeight;

	//Assert(s_DeviceContext != nullptr, "Failed to create device context!");

	//SetPixels(true);
	//s_RenderingContext = wglCreateContext(s_DeviceContext);

	//Assert(s_RenderingContext != nullptr, "Failed to create GL context!");

	//wglMakeCurrent(s_DeviceContext, s_RenderingContext);

	//RECT rect;

	//GetClientRect(s_Window, &rect);

	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearDepth(1.0F);
	//glLineWidth(5.0);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_NORMALIZE);

	//glViewport(0,0,s_WindowWidth, s_WindowHeight);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////static float lmodel_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	////static float lmodel_twoside[] = { GL_FALSE };
	////static float lmodel_local[] = { GL_FALSE };

	//static float light0_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	//static float light0_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	//static float light0_position[] = { 6.0f, 6.0f, 6.0f, 1.0f };
	//static float light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//static float bevel_mat_ambient[] = { 0.0f, 0.5f, 0.0f, 1.0f };
	//static float bevel_mat_shininess[] = { 20.0f };
	//static float bevel_mat_specular[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	//static float bevel_mat_diffuse[] = { 0.0f, 0.0f, 1.0f, 0.0f };

	//glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	////glEnable(GL_LIGHT0);

	////glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lmodel_local);
	////glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
	////glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	////glMaterialfv(GL_FRONT, GL_AMBIENT, bevel_mat_ambient);
	//glMaterialfv(GL_FRONT, GL_SHININESS, bevel_mat_shininess);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, bevel_mat_specular);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, bevel_mat_diffuse);

	//glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	//glDisable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	//glShadeModel(GL_SMOOTH);

	//CompileSphere();
}

//---------------------------------------------------------------------------

void Renderer::AddSphere(const Sphere& p_Sphere, LinearColour p_Colour)
{
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glTranslatef(p_Sphere.Centre.x, p_Sphere.Centre.y, p_Sphere.Centre.z);
	//glScalef(p_Sphere.Radius, p_Sphere.Radius, p_Sphere.Radius);

	//glColor3f(p_Colour.R, p_Colour.G, p_Colour.B);
	//glCallList(g_SphereList);

	//glPopMatrix();
}

//---------------------------------------------------------------------------

void Renderer::AddPlane(const Mathematics::Plane& p_Plane, LinearColour p_Colour)
{
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	////glTranslatef(p_Plane.Centre.x, p_Plane.Centre.y, p_Plane.Centre.z);
	////glScalef(p_Sphere.Radius, p_Sphere.Radius, p_Sphere.Radius);

	////glColor3f(p_Colour.R, p_Colour.G, p_Colour.B);
	////glCallList(g_SphereList);

	//glPopMatrix();
}

//---------------------------------------------------------------------------

void Renderer::AddLineSegment(const Mathematics::Point& p_Point1
							 , const Mathematics::Point& p_Point2
							 , LinearColour p_Colour)
{
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();

	//SetColour(p_Colour);

	//glBegin(GL_LINES);
	//glVertex3f(p_Point1.x, p_Point1.y, p_Point1.z);
	//glVertex3f(p_Point2.x, p_Point2.y, p_Point2.z);
	//glEnd();

	//glPopMatrix();
}

//---------------------------------------------------------------------------

void Renderer::Canvas()
{
	//	
	//scalar spin=static_cast<scalar>(2);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	////glRotated(spin,1.0,1.0,0.0);
	////glMultMatrixd(CameraMatrix);
	//glGetDoublev(GL_MODELVIEW_MATRIX, CameraMatrix);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45.0, s_AspectRatio,0.001,30.0);
	//glTranslated(0.0,0.0,-10.0);
}

//---------------------------------------------------------------------------

void Renderer::Paint()
{
	//wglMakeCurrent(s_DeviceContext, s_RenderingContext);
	//s_Exposure = 1;
}

//---------------------------------------------------------------------------

s32 Renderer::CheckExposure()
{
	s32 ret(s_Exposure);
	s_Exposure = 0;
	return ret;
}

//---------------------------------------------------------------------------

void Renderer::UpdatePalette()
{
	if (s_Palette != NULL)
	{
		SelectPalette(GetDC(s_Window), s_Palette, FALSE);
		RealizePalette(GetDC(s_Window));
	}
}

//---------------------------------------------------------------------------

void Renderer::SwapBuffer()
{
	//glFlush();
	//SwapBuffers(s_DeviceContext);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//---------------------------------------------------------------------------

void Renderer::SetPixels(bool p_UseDoubleBuffer)
{
	s_PixelDescriptor =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA,
		32, //color
		0, 0, 0, 0, 0, 0, 0, 0, //RGBA num bit and shift
		0, 0, 0, 0, 0, //Accumulator + RGBA bits
		24, // depth
		8, //stencil
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if (p_UseDoubleBuffer != 0)
	{
		s_PixelDescriptor.dwFlags |= PFD_DOUBLEBUFFER;
	}

	int pfm = ChoosePixelFormat(s_DeviceContext, &s_PixelDescriptor);
	if (pfm != 0)
	{
		if (SetPixelFormat(s_DeviceContext, pfm, &s_PixelDescriptor) != FALSE)
		{
			s_Palette = GetPalette();
			SelectPalette(s_DeviceContext, s_Palette, FALSE);
			RealizePalette(s_DeviceContext);
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

	n = GetPixelFormat(s_DeviceContext);
	DescribePixelFormat(s_DeviceContext, n, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

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
	return nullptr;
}

//---------------------------------------------------------------------------

void Renderer::SetColour(const LinearColour& p_Colour)
{
	//glColor4f(p_Colour.R, p_Colour.G, p_Colour.B, p_Colour.A);
}