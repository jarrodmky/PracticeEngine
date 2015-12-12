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
#include "Buffers.h"
#include "DataStructures.h"

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
			, m_TransformBuffer(p_System)
		{}

		NonCopyable(Camera);

	//Methods
	public:

		void Initialize(const Mathematics::Vector3& p_Position
			, const Mathematics::Vector3& p_Interest
						, const f32 p_FOV
						, const f32 p_FarZ
						, const f32 p_NearZ)
		{
			Transform.Set(Mathematics::J(), p_Interest - p_Position, p_Position);
			m_FieldOfViewAngle = p_FOV;
			m_NearPlane = p_NearZ;
			m_FarPlane = p_FarZ;

			m_TransformBuffer.Allocate();
		}

		void Update(const f32 p_DeltaTime);

		void Render()
		{
			CameraBuffer data;
			data.ViewPosition = MakePoint(Transform.GetPosition());
			data.WorldToViewToProjection = GetWorldToProjectionTransform().Transposition();

			m_TransformBuffer.Set(&data);
			m_TransformBuffer.BindToVertexShader(1);
		}

		void Terminate()
		{
			m_TransformBuffer.Free();
		}

		Mathematics::Matrix44 GetViewToWorldTransform() const
		{
			return Transform.GetLocalToWorld();
		}

		Mathematics::Matrix44 GetWorldToViewTransform() const
		{
			return Transform.GetWorldToLocal();
		}

		Mathematics::Matrix44 GetWorldToProjectionTransform() const
		{
			return GetPerspectiveTransform() * GetWorldToViewTransform();
		}

		Mathematics::Matrix44 GetPerspectiveTransform() const
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

		Visualization::ConstantBuffer<CameraBuffer> m_TransformBuffer;
	};
}

#endif // #ifndef IncludedVisuCameraH