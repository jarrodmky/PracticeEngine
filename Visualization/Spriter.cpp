//===========================================================================
// Filename:	Spriter.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Spriter.h"
#include <SpriteBatch.h>
#include "System.h"
#include "Texture.h"

using namespace Mathematics;
using namespace Visualization;

//===========================================================================
// Implementation Declarations
//===========================================================================

namespace
{
}


Spriter::Spriter()
: m_SpriteBatch(nullptr)
{

}

Spriter::~Spriter()
{
	Assert(m_SpriteBatch == nullptr, "Not released!")
}

void Spriter::Initialize(System& p_System)
{
	Assert(m_SpriteBatch == nullptr, "Already initialized!");
	m_SpriteBatch = new DirectX::SpriteBatch(p_System.GetContext());
}

void Spriter::Terminate()
{
	Assert(m_SpriteBatch != nullptr, "Not initialized!");
	ProperlyDelete(m_SpriteBatch);
}

void Spriter::BeginRender()
{
	Assert(m_SpriteBatch != nullptr, "Not initialized!");
	m_SpriteBatch->Begin();
}

void Spriter::EndRender()
{
	Assert(m_SpriteBatch != nullptr, "Not initialized!");
	m_SpriteBatch->End();
}

void Spriter::Draw(const Texture& p_Texture, const Mathematics::Vector2& p_Position)
{
	Assert(m_SpriteBatch != nullptr, "Not initialized!");
	m_SpriteBatch->Draw(p_Texture.m_Texture, *(DirectX::XMFLOAT2*)&p_Position);
}