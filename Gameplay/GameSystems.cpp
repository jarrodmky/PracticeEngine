//===========================================================================
// Filename:	GameObjectFactory.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"

#include "GameSystems.h"

namespace
{
	Visualization::System* s_gs = nullptr;
	Utilization::System* s_is = nullptr;
	Visualization::ModelManager* s_mm = nullptr;
	Visualization::TextureManager* s_textureManager = nullptr;
}

void Systems::Initialize(Visualization::System& p_GraphicsSystem
					, Utilization::System& p_InputSystem
					, Visualization::ModelManager& p_ModelManager
					, Visualization::TextureManager& p_TextureManager)
{

}

void Systems::Terminate()
{

}
