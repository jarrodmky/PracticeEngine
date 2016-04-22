#include "Precompiled.h"
#include "Rasterizer.h"
#include "System.h"

using namespace Visualization;

namespace
{
}

//===========================================================================
// Definitions
//===========================================================================

Rasterizer::Rasterizer()
	: m_RasterizerState(nullptr)
{
}

//---------------------------------------------------------------------------

Rasterizer::~Rasterizer()
{
	Assert(m_RasterizerState == nullptr, "DepthStencil not released!!");
}

//---------------------------------------------------------------------------

void Rasterizer::Initialize(System& p_System, CullMode p_CullMode, FillMode p_FillMode)
{
	Assert(!m_RasterizerState, "Depth stencil already initiliazed!");

	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	//set cull mode
	switch (p_CullMode)
	{
	case Visualization::Rasterizer::CullMode::None:
		desc.CullMode = D3D11_CULL_NONE;
		break;
	case Visualization::Rasterizer::CullMode::Clockwise:
		desc.CullMode = D3D11_CULL_FRONT;
		break;
	case Visualization::Rasterizer::CullMode::CounterClockwise:
		desc.CullMode = D3D11_CULL_BACK;
		break;
	default:
		break;
	}

	//set fill mode
	switch (p_FillMode)
	{
	case Visualization::Rasterizer::FillMode::Wireframe:
		desc.FillMode = D3D11_FILL_WIREFRAME;
		break;
	case Visualization::Rasterizer::FillMode::Solid:
		desc.FillMode = D3D11_FILL_SOLID;
		break;
	default:
		break;
	}

	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;

	HRESULT hr = p_System.GetDevice()->CreateRasterizerState(&desc, &m_RasterizerState);
	Assert(SUCCEEDED(hr), "Failed to create raster state!");
}

//---------------------------------------------------------------------------

void Rasterizer::Terminate()
{
	ProperlyRelease(m_RasterizerState);
}

//---------------------------------------------------------------------------
		
void Rasterizer::Bind(System& p_System)
{
	p_System.GetContext()->RSSetState(m_RasterizerState);
}