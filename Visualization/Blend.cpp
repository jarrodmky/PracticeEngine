#include "Precompiled.h"
#include "Blend.h"
#include "System.h"

using namespace Visualization;

namespace
{
	void Blending(System& p_System, ID3D11BlendState*& p_Blend, bool p_Additive)
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		if(p_Additive)
		{
			desc.AlphaToCoverageEnable = false;
			desc.IndependentBlendEnable = false;
			desc.RenderTarget[0].BlendEnable = true;
			desc.RenderTarget[0].SrcBlend	   = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlend	  = D3D11_BLEND_ONE;
			desc.RenderTarget[0].BlendOp	    = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
			desc.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}
		else
		{
			desc.AlphaToCoverageEnable = false;
			desc.IndependentBlendEnable = false;
			desc.RenderTarget[0].BlendEnable = false;
			desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
			desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		HRESULT hr = p_System.GetDevice()->CreateBlendState(&desc, &p_Blend);
		Assert(SUCCEEDED(hr), "Failed to create depth stencil!");
	}
}

//===========================================================================
// Definitions
//===========================================================================

Blend::Blend()
: m_Blend(nullptr)
{
}

//---------------------------------------------------------------------------

Blend::~Blend()
{
	Assert(m_Blend == nullptr, "Blend not released!!");
}

//---------------------------------------------------------------------------

void Blend::Initialize(System& p_System, BlendMethod p_BlendMode)
{
	Assert(!m_Blend, "Blending already initiliazed!");

	switch (p_BlendMode)
	{
	case Visualization::Blend::BlendMethod::Default:
		Blending(p_System, m_Blend, false);
		break;
	case Visualization::Blend::BlendMethod::Additive:
		Blending(p_System, m_Blend, true);
		break;
	default:
		Halt("Invalid blend method!!");
	}
}

//---------------------------------------------------------------------------

void Blend::Terminate()
{
	ProperlyRelease(m_Blend);
}

//---------------------------------------------------------------------------
		
void Blend::BindToOutput(System& p_System, u32 p_Index)
{
	f32 blendColour[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	p_System.GetContext()->OMSetBlendState(m_Blend, blendColour, 0xffffffff);
}