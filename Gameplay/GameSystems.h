#ifndef IncludedGameGameSystemsH
#define IncludedGameGameSystemsH

//===========================================================================
// Filename:	World.h
// Author:		Jarrod MacKay
// Description:	Defines a world where game objects are living.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "SafePool.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class Camera;
	class System;
	class ModelManager;
	class TextureManager;
}

namespace Utilization
{
	class System;
}

namespace Systems
{

		void Initialize(Visualization::System& p_GraphicsSystem
						, Utilization::System& p_InputSystem
						, Visualization::ModelManager& p_ModelManager
						, Visualization::TextureManager& p_TextureManager);
		void Terminate();

		Visualization::System& GetGraphicsSystem();
		Utilization::System& GetInputSystem();
		Visualization::ModelManager& GetModelManager();
		Visualization::TextureManager& GetTextureManager();
		
} // namespace Gameplay

#endif //#ifndef IncludedGameGameSystemsH