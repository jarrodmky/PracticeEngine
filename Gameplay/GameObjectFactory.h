#ifndef IncludedGameGameObjectFactoryH
#define IncludedGameGameObjectFactoryH

//===========================================================================
// Filename:	GameObjectFactory.h
// Author:		Jarrod MacKay
// Description:	Factory that creates game objects
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "GameObject.h"

//===========================================================================
// Classes
//===========================================================================

namespace Gameplay
{

	class GameObjectFactory
	{
	//Attributes
	private:

		GameObjectPool& m_Pool;

	//Operators
	public:

		GameObjectFactory(GameObjectPool& p_Pool);
		~GameObjectFactory();

	//Methods
	public:

		GameObjectHandle Create(const char* p_FileName);
		void Destroy(GameObjectHandle p_Ticket);
	};

} // namespace Gameplay

#endif //#ifndef IncludedGameGameObjectFactoryH