#ifndef IncludedGameTransformComponentH
#define IncludedGameTransformComponentH

//===========================================================================
// Filename:	TransformComponent.h
// Author:		Jarrod MacKay
// Description:	Defines a 3d space orientation position component.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Component.h"

namespace Meta
{
	class Class;
}


//===========================================================================
// Classes
//===========================================================================

namespace Gameplay
{
	class TransformComponent : public Component
	{
	
	//Attributes
	public:

		Mathematics::Frame Transform;

	//Operators
	public:

		MetaClassDeclare

		TransformComponent();
		virtual ~TransformComponent();

	//Methods
	public:

		virtual void Initialize() override;
	};

} // namespace Gameplay

#endif //#ifndef IncludedGameTransformComponentH