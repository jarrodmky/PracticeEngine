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

		Camera(System& p_System)
			: Transform()
			, m_FieldOfViewAngle()
			, m_NearPlane()
			, m_FarPlane()
			, m_System(p_System)
			, m_TransformBuffer()
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
			m_TransformBuffer.Initialize(m_System);
		}

		void Update(const f32 p_DeltaTime);

		void Render()
		{
			CameraBuffer data;
			data.ViewPosition = Transform.GetPosition().PositionVector();
			data.WorldToViewToProjection = (GetPerspectiveTransform() * GetWorldToViewTransform()).Transposition();

			m_TransformBuffer.Set(m_System, data);
			m_TransformBuffer.BindVS(m_System, 1);
		}

		void Terminate()
		{
			m_TransformBuffer.Terminate();
		}

		Mathematics::Matrix GetViewToWorldTransform() const
		{
			return Transform.LocalToWorld();
		}

		Mathematics::Matrix GetWorldToViewTransform() const
		{
			return Transform.WorldToLocal();
		}

		Mathematics::Matrix GetPerspectiveTransform() const
		{
			f32 h = static_cast<f32>(m_System.GetHeight());
			f32 w = static_cast<f32>(m_System.GetWidth());
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
		
		//rendering
		System& m_System;

		TypedConstantBuffer<CameraBuffer> m_TransformBuffer;
	};
}

#endif // #ifndef IncludedVisuCameraH