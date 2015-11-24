#include "Precompiled.h"
#include "Texture.h"

#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

using namespace Visualization;

//===========================================================================
// Definitions
//===========================================================================

Texture::Texture()
: m_Texture(nullptr)
{
}

//---------------------------------------------------------------------------

Texture::~Texture()
{
	Assert(m_Texture == nullptr, "Texture not released!!");
}

//---------------------------------------------------------------------------

void Texture::Initialize(System& p_System, const wchar_t* p_Filename)
{
	DirectX::CreateDDSTextureFromFile(p_System.GetDevice(), p_Filename, nullptr, &m_Texture);
	if(m_Texture == nullptr)
	{
		DirectX::CreateWICTextureFromFile(p_System.GetDevice(), p_Filename, nullptr, &m_Texture);
	}
}

//---------------------------------------------------------------------------

void Texture::Terminate()
{
	ProperlyRelease(m_Texture);
}

//---------------------------------------------------------------------------
		
void Texture::BindVertexShader(System& p_System, u32 p_Index)
{
	p_System.GetContext()->VSSetShaderResources(p_Index, 1, &m_Texture);
}

//---------------------------------------------------------------------------

void Texture::BindPixelShader(System& p_System, u32 p_Index)
{
	p_System.GetContext()->PSSetShaderResources(p_Index, 1, &m_Texture);
}