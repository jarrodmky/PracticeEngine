#ifndef IncludedGameComponentH
#define IncludedGameComponentH

//===========================================================================
// Filename:	Component.h
// Author:		Jarrod MacKay
// Description:	Defines a component-based game logic class.
//===========================================================================

#include <Meta.h>

//===========================================================================
// Classes
//===========================================================================

namespace Gameplay
{
	class GameObject;
	
	class Component
	{
	//Attributes
	private:

	friend class GameObject;

		GameObject* m_GameObject;

	//Operators
	public:
		
		MetaClassDeclare

		Component();
		virtual ~Component();

	//Methods
	public:

		virtual void Initialize() {}
		virtual void Terminate() {}
		virtual void Update(f32 p_DeltaTime) {}
		virtual void Render() {}

		GameObject& GetContainingObject() { return *m_GameObject;}
		const GameObject& GetContainingObject() const  { return *m_GameObject;}
	};

} // namespace Gameplay

#endif //#ifndef IncludedGameComponentH