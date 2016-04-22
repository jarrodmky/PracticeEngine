#ifndef IncludedGameCameraComponentH
#define IncludedGameCameraComponentH

//===========================================================================
// Filename:	CameraComponent.h
// Author:		Jarrod MacKay
// Description:	Defines a 3d space orientation position component.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Visualization.h>
#include "Component.h"

//===========================================================================
// Classes
//===========================================================================

namespace Gameplay
{
	class CameraComponent : public Component
	{
	
	//Attributes
	private :

		Visualization::Camera m_Camera;

	//Operators
	public:

		MetaClassDeclare

		CameraComponent();
		virtual ~CameraComponent();

	//Methods
	public:

		virtual void Initialize() override;

		Visualization::Camera& GetCamera() {return m_Camera;}
		const Visualization::Camera& GetCamera() const {return m_Camera;}
	};

} // namespace Gameplay

#endif //#ifndef IncludedGameCameraComponentH