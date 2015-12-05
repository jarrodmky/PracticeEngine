#include "Precompiled.h"
#include "DepthStencil.h"

using namespace Visualization;

namespace
{
	void MakeDepthStencil(System& p_System, ID3D11DepthStencilState*& p_DepthStencil, bool p_TestForDepth, bool p_WriteToDepthBuffer)
	{
		D3D11_DEPTH_STENCIL_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.DepthEnable = p_TestForDepth;
		desc.DepthWriteMask = p_WriteToDepthBuffer ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		desc.StencilEnable = false;
		desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

		desc.BackFace = desc.FrontFace;

		HRESULT hr = p_System.GetDevice()->CreateDepthStencilState(&desc, &p_DepthStencil);
		Assert(SUCCEEDED(hr), "Failed to create depth stencil!");
	}
}

//===========================================================================
// Definitions
//===========================================================================

DepthStencil::DepthStencil()
: m_DepthStencil(nullptr)
{
}

//---------------------------------------------------------------------------

DepthStencil::~DepthStencil()
{
	Assert(m_DepthStencil == nullptr, "DepthStencil not released!!");
}

//---------------------------------------------------------------------------

void DepthStencil::Initialize(System& p_System, DepthTest p_DepthTest)
{
	Assert(!m_DepthStencil, "Depth stencil already initiliazed!");

	switch (p_DepthTest)
	{
	case Visualization::DepthStencil::DepthTest::None:
		MakeDepthStencil(p_System, m_DepthStencil, false, false);
		break;
	case Visualization::DepthStencil::DepthTest::Default:
		MakeDepthStencil(p_System, m_DepthStencil, true, true);
		break;
	case Visualization::DepthStencil::DepthTest::Read:
		MakeDepthStencil(p_System, m_DepthStencil, true, false);
		break;
	default:
		Assert(false, "Invalid stencil!!");
	}
}

//---------------------------------------------------------------------------

void DepthStencil::Terminate()
{
	ProperlyRelease(m_DepthStencil);
}

//---------------------------------------------------------------------------
		
void DepthStencil::BindToOutput(System& p_System, u32 p_Index)
{
	p_System.GetContext()->OMSetDepthStencilState(m_DepthStencil, 0);
}