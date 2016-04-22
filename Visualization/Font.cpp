//====================================================================================================
// Filename:	Font.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Font.h"

#include "System.h"
#include <SpriteFont.h>
#include "Spriter.h"

using namespace Visualization;

//====================================================================================================
// Class Definitions
//====================================================================================================

Font::Font()
	: m_SpriteFont(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

Font::~Font()
{
	Assert(m_SpriteFont == nullptr, "Font not freed.");
}

//----------------------------------------------------------------------------------------------------
void Font::Initialize(System& p_System, const char* p_Filename)
{
	Assert(m_SpriteFont == nullptr, "Already initialized.");
	
	ID3D11Device* device = p_System.GetDevice();

	wchar_t wbuffer[1024];
	mbstowcs_s(nullptr, wbuffer, p_Filename, 1024);
	m_SpriteFont = new DirectX::SpriteFont(device, wbuffer);
}

//----------------------------------------------------------------------------------------------------
void Font::Terminate()
{
	Assert(m_SpriteFont != nullptr, "Already terminated.");
	ProperlyDelete(m_SpriteFont);
}

//----------------------------------------------------------------------------------------------------
void Font::QueueRender(const char* p_String, const Mathematics::Vector2& p_Position)
{
	wchar_t wbuffer[1024];
	mbstowcs_s(nullptr, wbuffer, p_String, 1024);
	QueueRender(wbuffer, p_Position);
}

//----------------------------------------------------------------------------------------------------
void Font::QueueRender(const wchar_t* p_String, const Mathematics::Vector2& p_Position)
{
	Assert(m_SpriteFont != nullptr, "Not initialized.");
	m_RenderQueue.push_back(TextMarker(p_String, p_Position));
}

void Font::Render(Spriter& p_Spriter)
{
	Assert(m_SpriteFont != nullptr, "Not initialized.");
	Assert(p_Spriter.m_SpriteBatch != nullptr, "Spriter not initialized.");
	for (auto marker : m_RenderQueue)
	{
		m_SpriteFont->DrawString(p_Spriter.m_SpriteBatch, marker.first.c_str(), DirectX::XMFLOAT2(marker.second(0), marker.second(1)));
	}
	m_RenderQueue.clear();
}