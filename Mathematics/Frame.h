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

namespace Mathematics 
{

//===========================================================================
// Classes
//===========================================================================

	class Frame
	{
	//Attributes
	private:

		const Vector Up = ConstantVectors::J;
		const Vector Forward = ConstantVectors::K;

		Vector m_Position;

		Quaternion m_Rotation;

	//Operators
	public:

		Frame()
			: m_Position()
			, m_Rotation()
		{}

	//Methods
	public:

		void Initialize(const Vector& p_Up = ConstantVectors::Zero
			, const Vector& p_Forward = ConstantVectors::J
			, const Point& p_Position = ConstantPoints::Origin)
		{
			m_Position = p_Position.PositionVector();

			//get rotation
		}

		const Vector GetForwardVector()
		{
			return RotatedVector(m_Rotation, Forward);
		}

		const Vector GetUpVector()
		{
			return RotatedVector(m_Rotation, Up);
		}

		const Vector GetLeftVector()
		{
			return RotatedVector(m_Rotation, Up * Forward);
		}

		const Matrix WorldToLocalTransform()
		{
			return ConstantMatrices::Identity;
		}
	};

}
#endif