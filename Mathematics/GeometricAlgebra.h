#ifndef IncludedMathGeometricAlgebraH
#define IncludedMathGeometricAlgebraH

//===========================================================================
// Filename:	GeometricAlgebra.h
// Author:		Jarrod MacKay
// Description:	Contains the classic(3-D), homogeneous(4-D) and
//				conformational(5-D) algebra of R^3
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>

namespace Mathematics
{
	namespace OriginalGeoAlg
	{
		struct Scalar;
		struct Vector;
		struct Bivector;
		struct Pseudoscalar;
		struct Multivector;

		struct Scalar
		{
			f32 Value;
		};

		struct Pseudoscalar
		{
			f32 Value;
		};

		struct Vector
		{
			f32 e1;
			f32 e2;
			f32 e3;
		};

		struct Bivector
		{
			f32 e2e3;
			f32 e1e3;
			f32 e1e2;
		};

		struct Multivector
		{
			Scalar S;
			Vector V;
			Bivector B;
			Pseudoscalar P;
		};


	}
}

#endif //#ifndef IncludedMathGeometricAlgebraH