#ifndef INCLUDED_GRAPHICS_SYSTEM_H
#define INCLUDED_GRAPHICS_SYSTEM_H

//====================================================================================================
// Filename:	GraphicsSystem.h
// Created by:	Peter Chan
// Description:	Class for the graphics system.
//====================================================================================================

#include "Common.h"
#include "LinearColour.h"

//====================================================================================================
// Namespace
//====================================================================================================

namespace Visualization
{

//====================================================================================================
// Class Declarations
//====================================================================================================
	

	enum IndexTopology
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip
	};

class System
{
public:

	System();
	~System();

	void Initialize(HWND window, bool fullscreen);
	void Terminate();

	void BeginRender(Visualization::LinearColour p_ClearColour = Visualization::ConstantColours::Black);
	void EndRender();

	void ToggleFullscreen();
	
	u32 GetWidth() const;
	u32 GetHeight() const;

	ID3D11Device* GetDevice()			{ return mpD3DDevice; }
	ID3D11DeviceContext* GetContext()	{ return mpImmediateContext; }
	
private:
	NonCopyable(System);

	ID3D11Device* mpD3DDevice;
	ID3D11DeviceContext* mpImmediateContext;

	IDXGISwapChain* mpSwapChain;
	ID3D11RenderTargetView* mpRenderTargetView;

	ID3D11Texture2D* mpDepthStencilBuffer;
	ID3D11DepthStencilView* mpDepthStencilView;

	D3D_DRIVER_TYPE mDriverType;
	D3D_FEATURE_LEVEL mFeatureLevel;

	DXGI_SWAP_CHAIN_DESC mSwapChainDesc;

	D3D11_VIEWPORT mViewport;

	BOOL mFullscreen;
};

} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_SYSTEM_H