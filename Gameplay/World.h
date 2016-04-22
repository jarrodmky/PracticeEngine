#ifndef IncludedGameWorldH
#define IncludedGameWorldH

//===========================================================================
// Filename:	World.h
// Author:		Jarrod MacKay
// Description:	Defines a world where game objects are living.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "GameObject.h"
#include "GameObjectFactory.h"

//===========================================================================
// Classes
//===========================================================================
namespace Visualization
{
	class Camera;
	class Terrain;
}


namespace Gameplay
{
	class World
	{
	//Definition
	private:

		typedef std::vector<GameObject*> GameObjectList;
		typedef std::vector<GameObjectHandle> DestroyList;

	//Attributes
	private:

		GameObjectPool m_Pool;
		GameObjectFactory m_Factory;
		GameObjectList m_UpdateList;
		DestroyList m_DestroyList;
		Visualization::Camera* m_Camera;
		Visualization::Terrain* m_Terrain;
		bool m_Updating;

		//Operators
	public:

		World(const u32 p_Capacity);
		~World();

		//Methods
	public:

		void Initialize();
		void Terminate();

		void LoadLevel(const char* p_Filename);

		GameObjectHandle Create(const char* p_Filename, const char* p_Name);
		GameObjectHandle Find(const char* p_Name);
		void Destroy(GameObjectHandle p_Handle);

		void Update(f32 p_DeltaTime);
		void Render();

		void SetMainCamera(Visualization::Camera* p_Camera) { m_Camera = p_Camera; }
		Visualization::Camera* GetMainCamera() { return m_Camera; }
		const Visualization::Camera* GetMainCamera() const { return m_Camera; }

		void SetTerrain(Visualization::Terrain* p_Terrain) { m_Terrain = p_Terrain; }
		Visualization::Terrain* GetMainTerrain() { return m_Terrain; }
		const Visualization::Terrain* GetMainTerrain() const { return m_Terrain; }

	private:

		void DestroyImmediately(GameObjectHandle p_Handle);
		void PurgeDestroyList();
	};

} // namespace Gameplay

#endif //#ifndef IncludedGameWorldH