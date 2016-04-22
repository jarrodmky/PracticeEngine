#include "Precompiled.h"
#include "Sampler.h"
#include "System.h"

using namespace Visualization;

namespace
{
	D3D11_FILTER GetFilter(Sampler::Filter p_Filter)
	{
		switch(p_Filter)
		{
		case Visualization::Sampler::Filter::Point:
		return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		case Visualization::Sampler::Filter::Linear:
		return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		case Visualization::Sampler::Filter::Anisotropic:
		return D3D11_FILTER_ANISOTROPIC;
		default:
		Halt("Invalid filter!!");
		}

		return D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
	}

	
	D3D11_TEXTURE_ADDRESS_MODE GetAddressMode(Sampler::AddressMode p_Mode)
	{
		switch(p_Mode)
		{
		case Sampler::AddressMode::Border:
		return D3D11_TEXTURE_ADDRESS_BORDER;
		case Sampler::AddressMode::Clamp:
		return D3D11_TEXTURE_ADDRESS_CLAMP;
		case Sampler::AddressMode::Mirror:
		return D3D11_TEXTURE_ADDRESS_MIRROR;
		case Sampler::AddressMode::Wrap:
		return D3D11_TEXTURE_ADDRESS_MIRROR;
		default:
		Halt("Invalid address mode!!");
		}

		return D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
	}
}

//===========================================================================
// Definitions
//===========================================================================

Sampler::Sampler()
: m_Sampler(nullptr)
{
}

//---------------------------------------------------------------------------

Sampler::~Sampler()
{
	Assert(m_Sampler == nullptr, "Sampler not released!!");
}

//---------------------------------------------------------------------------

void Sampler::Initialize(System& p_System, Filter p_Filter, AddressMode p_AddressMode)
{
	D3D11_FILTER filter = GetFilter(p_Filter);
	D3D11_TEXTURE_ADDRESS_MODE addressMode = GetAddressMode(p_AddressMode);

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = filter;
	sd.AddressU = addressMode;
	sd.AddressV = addressMode;
	sd.AddressW = addressMode;
	sd.BorderColor[0] = 1.0f;
	sd.BorderColor[1] = 1.0f;
	sd.BorderColor[2] = 1.0f;
	sd.BorderColor[3] = 1.0f;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = p_System.GetDevice()->CreateSamplerState(&sd, &m_Sampler);
	Assert(SUCCEEDED(hr), "Failed to create sampler!");
}

//---------------------------------------------------------------------------

void Sampler::Terminate()
{
	ProperlyRelease(m_Sampler);
}

//---------------------------------------------------------------------------
		
void Sampler::BindVertexShader(System& p_System, u32 p_Index)
{
	p_System.GetContext()->VSSetSamplers(p_Index, 1, &m_Sampler);
}

//---------------------------------------------------------------------------
		
void Sampler::BindGeometryShader(System& p_System, u32 p_Index)
{
	p_System.GetContext()->GSSetSamplers(p_Index, 1, &m_Sampler);
}

//---------------------------------------------------------------------------

void Sampler::BindPixelShader(System& p_System, u32 p_Index)
{
	p_System.GetContext()->PSSetSamplers(p_Index, 1, &m_Sampler);
}