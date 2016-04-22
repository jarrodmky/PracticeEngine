#include "Precompiled.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include "Texture.h"
#include "System.h"


using namespace Visualization;


//===========================================================================
// Definitions
//===========================================================================

Texture::Texture()
: m_Texture(nullptr)
{}

//---------------------------------------------------------------------------

Texture::~Texture()
{
	Assert(m_Texture == nullptr, "Texture not released!!");
}

//---------------------------------------------------------------------------

void Texture::Initialize(System& p_System, const wchar_t* p_Filename)
{
	ID3D11Device* device = p_System.GetDevice();

	DirectX::CreateDDSTextureFromFile(device, p_Filename, nullptr, &m_Texture);

	if(m_Texture == nullptr)
	{
		DirectX::CreateWICTextureFromFile(device, p_Filename, nullptr, &m_Texture);
	}
	Assert(m_Texture != nullptr, "Did not initialize form file %s!", p_Filename);
}

//---------------------------------------------------------------------------

void Texture::Terminate()
{
	ProperlyRelease(m_Texture);
}

//---------------------------------------------------------------------------

void Texture::BindVertexShader(System& p_System, u32 p_Index) const
{
	ID3D11DeviceContext* context = p_System.GetContext();
	Assert(m_Texture != nullptr, "Not initialized!");
	context->VSSetShaderResources(p_Index, 1, &m_Texture);
}

//---------------------------------------------------------------------------

void Texture::BindPixelShader(System& p_System, u32 p_Index) const
{
	ID3D11DeviceContext* context = p_System.GetContext();
	Assert(m_Texture != nullptr, "Not initialized!");
	context->PSSetShaderResources(p_Index, 1, &m_Texture);
}

//---------------------------------------------------------------------------

void Texture::UnbindVertexShader(System& p_System, u32 p_Index) const
{
	ID3D11DeviceContext* context = p_System.GetContext();
	static ID3D11ShaderResourceView* dummyTexture = nullptr;
	context->VSSetShaderResources(p_Index, 1, &dummyTexture);
}

//---------------------------------------------------------------------------

void Texture::UnbindPixelShader(System& p_System, u32 p_Index) const
{
	ID3D11DeviceContext* context = p_System.GetContext();
	static ID3D11ShaderResourceView* dummyTexture = nullptr;
	context->PSSetShaderResources(p_Index, 1, &dummyTexture);
}