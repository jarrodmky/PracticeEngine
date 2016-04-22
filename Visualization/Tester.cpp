#include "Precompiled.h"
#include "Tester.h"
#include "System.h"

using namespace Visualization;

namespace
{
	void DepthTesting(System& p_System, ID3D11DepthStencilState*& p_DepthStencil, bool p_TestForDepth)
	{
		D3D11_DEPTH_STENCIL_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.DepthEnable = p_TestForDepth;
		desc.DepthWriteMask = p_TestForDepth ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
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

	void Blending(System& p_System, ID3D11DepthStencilState*& p_DepthStencil)
	{
		D3D11_DEPTH_STENCIL_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS;

		desc.StencilEnable = true;
		desc.StencilReadMask = 0xff;
		desc.StencilWriteMask = 0xff;

		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
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

Tester::Tester()
: m_DepthStencilState(nullptr)
{
}

//---------------------------------------------------------------------------

Tester::~Tester()
{
	Assert(m_DepthStencilState == nullptr, "DepthStencil not released!!");
}

//---------------------------------------------------------------------------

void Tester::Initialize(System& p_System, DepthTest p_DepthTest)
{
	Assert(!m_DepthStencilState, "Depth stencil already initiliazed!");

	switch (p_DepthTest)
	{
	case Visualization::Tester::DepthTest::None:
		DepthTesting(p_System, m_DepthStencilState, false);
		break;
	case Visualization::Tester::DepthTest::Default:
		DepthTesting(p_System, m_DepthStencilState, true);
		break;
	case Visualization::Tester::DepthTest::AdditiveBlend:
		Blending(p_System, m_DepthStencilState);
		break;
	default:
		Halt("Invalid stencil!!");
	}
}

//---------------------------------------------------------------------------

void Tester::Terminate()
{
	ProperlyRelease(m_DepthStencilState);
}

//---------------------------------------------------------------------------
		
void Tester::BindToOutput(System& p_System)
{
	p_System.GetContext()->OMSetDepthStencilState(m_DepthStencilState, 0);
}