#ifndef IncludedGameColliderComponentH
#define IncludedGameColliderComponentH

//===========================================================================
// Filename:	ColliderComponent.h
// Author:		Jarrod MacKay
// Description:	Defines a provider of collision data
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Component.h"

//===========================================================================
// Classes
//===========================================================================

namespace Gameplay
{
	class TransformComponent;

	class ColliderComponent : public Component
	{
	
	//Attributes
	private:

		Mathematics::AABB3 m_BoundingVolume;
		Mathematics::LinearColour m_Colour;

	//Operators
	public:

		MetaClassDeclare

		ColliderComponent();
		virtual ~ColliderComponent();

	//Methods
	public:

		virtual void Initialize() override;
		virtual void Render() override;

		void SetCentre(const Mathematics::Vector3& p_Centre) {}
		void SetExtend(const Mathematics::Vector3& p_Extend) {}
		void SetColour(const Mathematics::LinearColour& p_Colour) {}

		const Mathematics::AABB3 GetAABB() const;
	};

} // namespace Gameplay

#endif //#ifndef IncludedGameColliderComponentH