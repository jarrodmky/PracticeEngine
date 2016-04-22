#ifndef IncludedGameGameObjectH
#define IncludedGameGameObjectH

//===========================================================================
// Filename:	GameObject.h
// Author:		Jarrod MacKay
// Description:	Defines a component-based game logic class.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Abstracts.h>

//===========================================================================
// Classes
//===========================================================================

namespace Gameplay
{
	class World;
	class Component;
	class GameObject;

	typedef Abstracts::Handle<GameObject> GameObjectHandle;
	typedef Abstracts::SafePool<GameObject> GameObjectPool;

	class GameObject
	{
		//Definition
	private:

		typedef std::vector<Component*> Components;

		//Attributes
	private:
		friend class World;

		GameObjectHandle m_Handle;
		std::string m_Name;
		World* m_World;
		Components m_Components;

		//Operators
	public:

		GameObject();
		~GameObject();

		//Methods
	public:

		void Initialize();
		void Terminate();
		void Update(f32 p_DeltaTime);
		void Render();

		void AddComponent(Component* p_Component);

		template <typename t_Type>
		bool FindComponent(const t_Type*& p_Component) const;

		template <typename t_Type>
		bool GetComponent(t_Type*& p_Component);

		World& GetWorld();
		const World& GetWorld() const;

		const char* GetName() const { return m_Name.c_str(); }
		GameObjectHandle GetHandle() const { return m_Handle; }

	private:

		template <typename t_Type>
		bool ComponentSearch(const t_Type*& p_Component) const;

		template <typename t_Type>
		bool ComponentSearch(t_Type*& p_Component);
	};

	template <typename t_Type>
	bool GameObject::FindComponent(const t_Type*& p_Component) const
	{
		return ComponentSearch(p_Component);
	}

	template <typename t_Type>
	bool GameObject::GetComponent(t_Type*& p_Component)
	{
		bool found = ComponentSearch(p_Component);
			//Assert(found, "Could not find %s!", t_Type::StaticGetMetaClass()->GetName());
			return false;
	}

	template <typename t_Type>
	bool GameObject::ComponentSearch(const t_Type*& p_Component) const
	{
		for(Component* c : m_Components)
		{
			if(c->GetMetaClass() == t_Type::StaticGetMetaClass())
			{
				p_Component = static_cast<t_Type*>(c);
				return true;
			}
		}
		return false;
	}

	template <typename t_Type>
	bool GameObject::ComponentSearch(t_Type*& p_Component)
	{
		for(Component* c : m_Components)
		{
			if(c->GetMetaClass() == t_Type::StaticGetMetaClass())
			{
				p_Component = static_cast<t_Type*>(c);
				return true;
			}
		}
		return false;
	}

} // namespace Gameplay

#endif //#ifndef IncludedGameGameObjectH