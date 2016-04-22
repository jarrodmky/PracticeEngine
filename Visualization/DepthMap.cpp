//===========================================================================
// Filename:	DepthMap.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "DepthMap.h"

//===========================================================================
// Classes
//===========================================================================

using namespace Mathematics;
using namespace Visualization;

namespace
{
}

//===========================================================================
// Class Definitions
//===========================================================================

DepthMap::DepthMap(System& p_System)
: m_System(p_System)
, m_ShaderResourceView(nullptr)
, m_DepthStencilViewer(nullptr)
, m_Viewport()
{}

//---------------------------------------------------------------------------

DepthMap::~DepthMap()
{
	Assert(m_ShaderResourceView == nullptr 
		   && m_DepthStencilViewer == nullptr, "Not released!")
}

//---------------------------------------------------------------------------

void DepthMap::Initialize(const u32 p_Width, const u32 p_Height)
{
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = p_Width;
	desc.Height = p_Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ID3D11Texture2D* texture = nullptr;
	HRESULT hr = m_System.GetDevice()->CreateTexture2D(&desc, nullptr, &texture);
	Assert(SUCCEEDED(hr), "failed to create render target texture");

	D3D11_SHADER_RESOURCE_VIEW_DESC resourceDesc;
	ZeroMemory(&resourceDesc, sizeof(resourceDesc));
	resourceDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	resourceDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	resourceDesc.Texture2D.MipLevels = 1;

	hr = m_System.GetDevice()->CreateShaderResourceView(texture, &resourceDesc, &m_ShaderResourceView);
	Assert(SUCCEEDED(hr), "failed to create shader resource view");

	D3D11_DEPTH_STENCIL_VIEW_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	hr = m_System.GetDevice()->CreateDepthStencilView(texture, &depthDesc, &m_DepthStencilViewer);
	Assert(SUCCEEDED(hr), "failed to create shader resource view");
	ProperlyRelease(texture);
	
	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.Width = static_cast<f32>(p_Width);
	m_Viewport.Height = static_cast<f32>(p_Height);
	m_Viewport.MaxDepth = 1.0f;
	m_Viewport.MinDepth = 0.0f;

}

//---------------------------------------------------------------------------

void DepthMap::Terminate()
{
	ProperlyRelease(m_DepthStencilViewer);
	ProperlyRelease(m_ShaderResourceView);
}

//---------------------------------------------------------------------------

void DepthMap::BeginRender()
{
	ID3D11DeviceContext* context(m_System.GetContext());
	context->ClearDepthStencilView(m_DepthStencilViewer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	static ID3D11RenderTargetView* nullRenderTargetView = nullptr;
	context->OMSetRenderTargets(1, &nullRenderTargetView, m_DepthStencilViewer);
	context->RSSetViewports(1, &m_Viewport);
}

//---------------------------------------------------------------------------

void DepthMap::EndRender()
{
	m_System.ResetRenderTarget();
	m_System.ResetViewport();
}

//---------------------------------------------------------------------------

void DepthMap::BindPixelShader(u32 p_Index)
{
	m_System.GetContext()->PSSetShaderResources(p_Index, 1, &m_ShaderResourceView);
}

//---------------------------------------------------------------------------

void DepthMap::UnbindPixelShader(u32 p_Index)
{
	static ID3D11ShaderResourceView* dummyTexture = nullptr;
	m_System.GetContext()->PSSetShaderResources(p_Index, 1, &dummyTexture);
}