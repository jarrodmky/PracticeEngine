#ifndef IncludedVisuCameraH
#define IncludedVisuCameraH

//===========================================================================
// Filename:	Camera.h
// Author:		Jarrod MacKay
// Description:	Defines a camera that can be placed in the world
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class Camera
	{
	//Operators
	public:

		Camera()
		{

		}

		NonCopyable(Camera);

	//Methods
	public:

		void Initialize(Mathematics::Point p_Position, Mathematics::Point p_Interest);

		void Update(f32 p_DeltaTime);

		Mathematics::Vector GetWorldForwardVector();

		Mathematics::Matrix GetWorldToCameraTransform();

		Mathematics::Matrix GetPerspectiveTransform();

	//Attributes
	private:

		const Mathematics::Vector k_Up = Mathematics::ConstantVectors::J;

		const Mathematics::Vector k_Forward = Mathematics::ConstantVectors::K;

		//extrinsic properties
		Mathematics::Frame m_Frame;

		//intrinsic properties
		f32 m_FieldOfViewAngle;

		f32 m_NearPlane;

		f32 m_FarPlane;
	};
}

#endif // #ifndef IncludedVisuCameraH