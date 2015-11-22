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

		Frame(const Vector& p_Forward = ConstantVectors::K
			, const Vector& p_Position = ConstantVectors::Zero
			, const Vector& p_Up = ConstantVectors::J)
			: m_Position(p_Position)
			, m_Rotation()
		{}

	//Methods
	public:

		const Vector GetForwardVector()
		{
			return RotatedVector(m_Rotation, Forward);
		}

		const Vector GetUpVector()
		{
			return RotatedVector(m_Rotation, Up);
		}

		const Matrix WorldToLocalTransform()
		{

		}
	};

}
#endif