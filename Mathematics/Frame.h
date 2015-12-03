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

		//Quaternion m_Rotation;
		//std::shared_ptr<Frame> m_RelativeFrame;

		Vector m_Origin;

		Vector m_Up;

		Vector m_Forward;

		//Vector m_Scale;

	//Operators
	public:

		Frame()
			//: m_Rotation(ConstantQuaternions::Identity)
			: m_Origin()
			, m_Up()
			, m_Forward()
		{}

	//Methods
	public:

		void Set(const Point& p_Position = ConstantPoints::Origin
			, const Vector& p_Forward = ConstantVectors::K
			, const Vector& p_Up = ConstantVectors::J)
		{
			m_Origin = p_Position.PositionVector();

			m_Forward = p_Forward;
			Vector left = p_Up * p_Forward;
			m_Up = m_Forward * left;

			Renormalize();
		}

		void Set(const Vector& p_Up
			, const Vector& p_Forward
			, const Point& p_Position = ConstantPoints::Origin)
		{
			Set(p_Position, p_Forward, p_Up);
		}

		//access
		const Vector GetLeft() const
		{
			return m_Up * m_Forward;
		}

		const Vector GetRight() const
		{
			return -(m_Up * m_Forward);
		}

		const Vector GetUp() const
		{
			return m_Up;
		}

		const Vector GetForward() const
		{
			return m_Forward;
		}

		const Point GetPosition() const
		{
			return Point(m_Origin);
		}

		const Matrix WorldToLocal() const
		{
			return Translation(m_Origin) * Rotation();
		}

		const Matrix LocalToWorld() const
		{
			return Rotation().Transposition() * Translation(-m_Origin);
		}

		const Matrix Rotation() const
		{
			return Matrix(GetRight(), GetUp(), GetForward());
		}

		//translations
		void Translate(const Vector& p_Displacement)
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
		void Rotate(const Vector& p_Axis, const scalar p_Angle)
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

		//renormalize
		void Renormalize()
		{
			m_Forward = m_Forward.Direction();
			Vector left = m_Up * m_Forward;
			m_Up = (m_Forward * left).Direction();
		}
	};
}
#endif