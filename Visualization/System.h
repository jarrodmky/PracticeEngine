#ifndef INCLUDED_GRAPHICS_SYSTEM_H
#define INCLUDED_GRAPHICS_SYSTEM_H

//====================================================================================================
// Filename:	GraphicsSystem.h
// Created by:	Peter Chan
// Description:	Class for the graphics system.
//====================================================================================================

#include "Common.h"
#include <Mathematics.h>
#include "Dashboard.h"

//====================================================================================================
// Namespace
//====================================================================================================

namespace Visualization
{

//====================================================================================================
// Class Declarations
//====================================================================================================

class System
{
public:

	System();
	~System();

	void Initialize(HWND window, bool fullscreen);
	void Terminate();

	void BeginRender(Mathematics::LinearColour p_ClearColour = Mathematics::ColourPallet::Black);
	void EndRender();

	void ResetRenderTarget();
	void ResetViewport();

	void ToggleFullscreen();
	
	u32 GetWidth() const;
	u32 GetHeight() const;
	u32 GetCentreX() const;
	u32 GetCentreY() const;
	f64 GetAspectRatio() const;
	Mathematics::Vector2 GetCentre() const;
	Mathematics::UintVector2 GetScreenWidthHeight() const;

	ID3D11Device* GetDevice()			{ return mpD3DDevice; }
	ID3D11DeviceContext* GetContext()	{ return mpImmediateContext; }

public:

	Dashboard ControlPanel;
	
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