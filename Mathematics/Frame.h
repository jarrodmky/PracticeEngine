#ifndef IncludedMathFrameH
#define IncludedMathFrameH

//===========================================================================
// Filename:	Frame.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional orthonormal
//				basis relative to some other frame (that frame is taken as
//				f = {i, j, j, O} or cartesian coordinates)
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Algebra.h"
#include "Geometry.h"

namespace Mathematics 
{

//===========================================================================
// Classes
//===========================================================================

	class Frame
	{
	//Attributes
	private:

		//TODO use scale!

		//std::shared_ptr<Frame> m_RelativeFrame;

		Vector3 m_Origin;

		Vector3 m_Up;

		Vector3 m_Forward;

		Vector3 m_Scale;

	//Operators
	public:

		Frame()
			: m_Origin(Zero3())
			, m_Up(J())
			, m_Forward(K())
			, m_Scale(Ones3())
		{}

	//Methods
	public:
		
		void Set(const Vector3& p_Up = J()
			, const Vector3& p_Forward = K()
			, const Vector3& p_Position = Zero3())
		{
			m_Origin = p_Position;

			m_Forward = p_Forward;
			Vector3 left = p_Up * p_Forward;
			m_Up = m_Forward * left;

			Renormalize();
		}

		void SetPosition(const Vector3& p_Position)
		{
			Set(GetUp(), GetForward(), p_Position);
		}

		//access
		const Vector3 GetLeft() const
		{
			return m_Up * m_Forward;
		}

		const Vector3 GetRight() const
		{
			return -(m_Up * m_Forward);
		}

		const Vector3 GetUp() const
		{
			return m_Up;
		}

		const Vector3 GetForward() const
		{
			return m_Forward;
		}

		const Vector3 GetPosition() const
		{
			return m_Origin;
		}

		const Matrix44 GetLocalToWorld() const
		{
			return Translation(m_Origin) * GetRotation() * GetScaling();
		}

		const Matrix44 GetWorldToLocal() const
		{
			return MakeMatrix(ScalingInverse(m_Scale)) * GetRotation().Transposition() * Translation(-m_Origin);
		}

		const Matrix44 GetLocalToWorldNS() const
		{
			return Translation(m_Origin) * GetRotation();
		}

		const Matrix44 GetWorldToLocalNS() const
		{
			return GetRotation().Transposition() * Translation(-m_Origin);
		}

		const Matrix44 GetRotation() const
		{
			return MakeMatrix(MakeMatrix(GetLeft(), GetUp(), GetForward()));
		}

		const Matrix44 GetScaling() const
		{
			return MakeMatrix(Scaling(m_Scale));
		}

		//translations
		void Translate(const Vector3& p_Displacement)
		{
			m_Origin += p_Displacement;
		}

		void MoveUp(const f32 p_Distance)
		{
			Translate(GetUp() * p_Distance);
		}

		void MoveDown(const f32 p_Distance)
		{
			Translate(-GetUp() * p_Distance);
		}

		void MoveForward(const f32 p_Distance)
		{
			Translate(GetForward() * p_Distance);
		}

		void MoveBack(const f32 p_Distance)
		{
			Translate(-GetForward() * p_Distance);
		}

		void MoveLeft(const f32 p_Distance)
		{
			Translate(GetLeft() * p_Distance);
		}

		void MoveRight(const f32 p_Distance)
		{
			Translate(GetRight() * p_Distance);
		}

		//rotations
		void Rotate(const Vector3& p_Axis, const scalar p_Angle)
		{
			Quaternion rotator(p_Axis, p_Angle);
			rotator.RotateVector(m_Up);
			rotator.RotateVector(m_Forward);
			Renormalize();
		}

		void Roll(const scalar p_Angle)
		{
			Rotate(GetForward(), p_Angle);
		}

		void Pitch(const scalar p_Angle)
		{
			Rotate(GetRight(), p_Angle);
		}

		void Yaw(const scalar p_Angle)
		{
			Rotate(GetUp(), p_Angle);
		}

		//scalings
		void Scale(const scalar p_Scale)
		{
			m_Scale = Vector3(p_Scale);
		}

		//renormalize
		void Renormalize()
		{
			m_Forward = m_Forward.Direction();
			Vector3 left = m_Up * m_Forward;
			m_Up = (m_Forward * left).Direction();
		}
	};
}
#endif