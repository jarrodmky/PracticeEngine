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
			: Transform()
			, m_FieldOfViewAngle()
			, m_NearPlane()
			, m_FarPlane()
		{}

		NonCopyable(Camera);

	//Methods
	public:

		void Initialize(const Mathematics::Point& p_Position
						, const Mathematics::Point& p_Interest
						, const f32 p_FOV
						, const f32 p_FarZ
						, const f32 p_NearZ)
		{
			Transform.Set(p_Position, p_Interest - p_Position);
			m_FieldOfViewAngle = p_FOV;
			m_NearPlane = p_NearZ;
			m_FarPlane = p_FarZ;
		}

		void Update(const f32 p_DeltaTime);

		Mathematics::Matrix GetViewToWorldTransform() const
		{
			return Transform.WorldToLocal();
		}

		Mathematics::Matrix GetWorldToViewTransform() const
		{
			return Transform.LocalToWorld();
		}

		Mathematics::Matrix GetPerspectiveTransform(const System& p_System) const
		{
			f32 h = static_cast<f32>(p_System.GetHeight());
			f32 w = static_cast<f32>(p_System.GetWidth());
			return Mathematics::PerspectiveProjection_LH(m_FieldOfViewAngle, w/h, m_FarPlane, m_NearPlane);
		}

	//Attributes
	public:

		//extrinsic properties
		Mathematics::Frame Transform;

	private:

		//intrinsic properties
		f32 m_FieldOfViewAngle;

		f32 m_NearPlane;

		f32 m_FarPlane;
	};
}

#endif // #ifndef IncludedVisuCameraH