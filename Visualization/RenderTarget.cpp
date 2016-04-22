//===========================================================================
// Filename:	RenderTarget.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "RenderTarget.h"

//===========================================================================
// Classes
//===========================================================================

using namespace Mathematics;
using namespace Visualization;

namespace
{
	DXGI_FORMAT GetFormat(RenderTarget::Format p_Format)
	{
		switch(p_Format)
		{
		case Visualization::RenderTarget::Format::R_F16:
		return DXGI_FORMAT_R16_FLOAT;
		case Visualization::RenderTarget::Format::RGBA_U8:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
		case Visualization::RenderTarget::Format::RGBA_F16:
		return DXGI_FORMAT_R16G16B16A16_FLOAT;
		default:
		Halt("Invalid format!");
		break;
		}
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}
}

//===========================================================================
// Class Definitions
//===========================================================================

RenderTarget::RenderTarget(System& p_System)
: m_System(p_System)
, m_Texture(nullptr)
, m_Target(nullptr)
, m_Stencil(nullptr)
, m_Viewport()
{}

//---------------------------------------------------------------------------

RenderTarget::~RenderTarget()
{
	Assert(m_Texture == nullptr 
		   && m_Target == nullptr 
		   && m_Stencil == nullptr, "Not released!")
}

//---------------------------------------------------------------------------

void RenderTarget::Initialize(const u32 p_Width, const u32 p_Height, const Format p_Format)
{
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = p_Width;
	desc.Height = p_Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = GetFormat(p_Format);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ID3D11Texture2D* texture = nullptr;
	HRESULT hr = m_System.GetDevice()->CreateTexture2D(&desc, nullptr, &texture);
	Assert(SUCCEEDED(hr), "failed to create render target texture");

	hr = m_System.GetDevice()->CreateShaderResourceView(texture, nullptr, &m_Texture);
	Assert(SUCCEEDED(hr), "failed to create shader view");

	hr = m_System.GetDevice()->CreateRenderTargetView(texture, nullptr, &m_Target);
	Assert(SUCCEEDED(hr), "failed to create render target");
	ProperlyRelease(texture);

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	hr = m_System.GetDevice()->CreateTexture2D(&desc, nullptr, &texture);
	Assert(SUCCEEDED(hr), "failed to create depth stencil texture");
	
	hr = m_System.GetDevice()->CreateDepthStencilView(texture, nullptr, &m_Stencil);
	Assert(SUCCEEDED(hr), "failed to create depth stencil view");
	ProperlyRelease(texture);

	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.Width = static_cast<f32>(p_Width);
	m_Viewport.Height = static_cast<f32>(p_Height);
	m_Viewport.MaxDepth = 1.0f;
	m_Viewport.MinDepth = 0.0f;

}

//---------------------------------------------------------------------------

void RenderTarget::Terminate()
{
	ProperlyRelease(m_Stencil);
	ProperlyRelease(m_Target);
	ProperlyRelease(m_Texture);
}

//---------------------------------------------------------------------------

void RenderTarget::BeginRender()
{
	f32 clearColour[4] = {0.5f, 0.5f, 0.5f, 1.0f};

	ID3D11DeviceContext* context(m_System.GetContext());

	context->ClearRenderTargetView(m_Target, clearColour);
	context->ClearDepthStencilView(m_Stencil, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, &m_Target, m_Stencil);
	context->RSSetViewports(1, &m_Viewport);
}

//---------------------------------------------------------------------------

void RenderTarget::EndRender()
{
	m_System.ResetRenderTarget();
	m_System.ResetViewport();
}

//---------------------------------------------------------------------------

void RenderTarget::BindTexture(u32 p_Index)
{
	m_System.GetContext()->PSSetShaderResources(p_Index, 1, &m_Texture);
}

//---------------------------------------------------------------------------

void RenderTarget::UnbindTexture(u32 p_Index)
{
	static ID3D11ShaderResourceView* dummyTexture = nullptr;
	m_System.GetContext()->PSSetShaderResources(p_Index, 1, &dummyTexture);
}