#ifndef IncludedMathFrameH
#define IncludedMathFrameH

//===========================================================================
// Filename:	Frame.h
// Author:		Jarrod MacKay
// Description:	Defines a class that represents a 3 dimensional orthonormal
//				basis relative to the standard basis.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinearAlgebra.h"
#include "Planar.h"

namespace Mathematics
{

	//===========================================================================
	// Classes
	//===========================================================================

	class Frame
	{
	//Attributes
	private:

		//TODO use scale and store 3rd vector!

		Vector3 m_Origin;

		//Quaternion m_Orientation;

		Vector3 m_Up;

		Vector3 m_Forward;

		//Operators
	public:

		Frame(const Vector3& p_Up = WorldUp()
			, const Vector3& p_Forward = WorldForward()
			, const Vector3& p_Position = Zero3())
			: m_Origin(p_Position)
			, m_Up(p_Up)
			, m_Forward(p_Forward)
			//, m_Orientation()
		{
			SetOrientation(p_Forward, p_Up);
		}

	//Methods
	public:

		inline void SetPosition(const Vector3& p_Position = Zero3())
		{
			m_Origin = p_Position;
		}

		inline void SetOrientation(const Vector3& p_Forward = WorldForward()
								 , const Vector3& p_Up = WorldUp())
		{
			Assert(p_Forward.IsUnit(), "Not unit forward!");
			Assert(p_Up.IsUnit(), "Not unit up!");
			m_Up = p_Up;
			m_Forward = p_Forward;
			//Reorient(p_Up, p_Forward);
		}

		//access

		inline const Vector3 GetRight() const
		{
			return m_Forward * m_Up;
			//return m_Orientation.Rotate(WorldRight());
		}

		inline const Vector3 GetLeft() const
		{
			return -GetRight();
		}

		inline const Vector3 GetUp() const
		{
			return m_Up;
			//return m_Orientation.Rotate(WorldUp());
		}

		inline const Vector3 GetForward() const
		{
			return m_Forward;
			//return m_Orientation.Rotate(WorldForward());
		}

		inline const Vector3 GetPosition() const
		{
			return m_Origin;
		}

		inline const Matrix44 GetRotation() const
		{
			return MakeChangeOfBasis(GetRight(), GetUp(), GetForward());
			//return MakeRotation(m_Orientation);
		}

		//inline const Quaternion GetOrientation() const
		//{
		//	return m_Orientation;
		//}

		inline const Matrix44 GetLocalToWorld() const
		{
			return MakeTranslation(m_Origin) * GetRotation();
		}

		inline const Matrix44 GetWorldToLocal() const
		{
			return GetRotation().Transposition() * MakeTranslation(-m_Origin);
		}

		//translations
		inline void Translate(const Vector3& p_Displacement)
		{
			m_Origin += p_Displacement;
		}

		inline void MoveUp(const f32 p_Distance)
		{
			Translate(GetUp() * p_Distance);
		}

		inline void MoveDown(const f32 p_Distance)
		{
			Translate(-GetUp() * p_Distance);
		}

		inline void MoveForward(const f32 p_Distance)
		{
			Translate(GetForward() * p_Distance);
		}

		inline void MoveBack(const f32 p_Distance)
		{
			Translate(-GetForward() * p_Distance);
		}

		inline void MoveLeft(const f32 p_Distance)
		{
			Translate(GetLeft() * p_Distance);
		}

		inline void MoveRight(const f32 p_Distance)
		{
			Translate(GetRight() * p_Distance);
		}

		void Renormalize();

		//rotations
		void Rotate(const Vector3& p_Axis, const scalar p_Angle)
		{
			Quaternion rotator(p_Axis, p_Angle);
			rotator.Rotate(m_Up);
			rotator.Rotate(m_Forward);

			//m_Orientation = rotator * m_Orientation;

			Renormalize();
		}

		inline void Roll(const scalar p_Angle)
		{
			Rotate(GetForward(), p_Angle);
		}

		inline void Pitch(const scalar p_Angle)
		{
			Rotate(GetRight(), p_Angle);
		}

		inline void Yaw(const scalar p_Angle)
		{
			Rotate(GetUp(), p_Angle);
		}

	};
}
#endif