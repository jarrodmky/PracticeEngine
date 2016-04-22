#ifndef IncludedMathTriangleH
#define IncludedMathTriangleH

//===========================================================================
// Filename:	Triangle.h
// Author:		Jarrod MacKay
// Description:	Defines an infinite straight Triangle.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "LinearAlgebra.h"
#include "Linear.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	template <u32 t_Dimension>
	class Triangle;

	//===========================================================================
	// Specialization (t_Dimension = 2)
	//===========================================================================

	template <>
	class Triangle<2>
	{
		//Operators
	public:

		Triangle(const Vector2& p_Point1, const Vector2& p_Point2, const Vector2& p_Point3)
			: First(p_Point1)
			, Second(p_Point2)
			, Third(p_Point3)
		{
			Assert(!Collinear(p_Point1, p_Point2, p_Point3), "Degenerate triangle!");
		}

		//Methods
	public:

		const Vector2 Centre()
		{
			return (First + Second + Third) * 0.333333333333333f;
		}

		void ConvertToBarycentric(Vector2& p_Point)
		{
			const Vector2 v0(Second - First);
			const Vector2 v1(Third - First);

			const scalar d00(v0 | v0);
			const scalar d01(v0 | v1);
			const scalar d11(v1 | v1);
			const scalar denom(d00 * d11 - d01 * d01);
			ConvertToBarycentric(v0, d00, v1, d11, d01, denom, p_Point);
		}

		bool Contains(const Vector2& p_Point)
		{
			Vector2 test(p_Point);
			ConvertToBarycentric(test);
			return test(1) >= Zero && test(2) >= Zero && test(1) + test(2) <= Unity;
		}

	private:

		void ConvertToBarycentric(const Vector2& p_Side0, const scalar p_Side0LenSq
			, const Vector2& p_Side1, const scalar p_Side1LenSq
			, const scalar p_Dot0To1, const scalar p_CrossDenom, Vector2& p_Point)
		{
			const Vector2 v2(p_Point - First);
			const scalar d20(v2 | p_Side0);
			const scalar d21(v2 | p_Side1);

			p_Point(1) = (p_Side1LenSq * d20 - p_Dot0To1 * d21) / p_CrossDenom;
			p_Point(2) = (p_Side0LenSq * d21 - p_Dot0To1 * d20) / p_CrossDenom;
			p_Point(0) = Unity - p_Point(1) - p_Point(2);

		}

		//Attributes
	public:

		Vector2 First;
		Vector2 Second;
		Vector2 Third;
	};

	//===========================================================================
	// Specialization (t_Dimension = 3)
	//===========================================================================

	template <>
	class Triangle<3>
	{
	//Operators
	public:

		Triangle(const Vector3& p_Point1, const Vector3& p_Point2, const Vector3& p_Point3)
			: First(p_Point1)
			, Second(p_Point2)
			, Third(p_Point3)
		{
			Assert(!Collinear(p_Point1, p_Point2, p_Point3), "Degenerate triangle!");
		}

	//Methods
	public:

		const Vector3 Centre() const
		{
			return (First + Second + Third) * 0.333333333333333f;
		}

		const Vector3 Normal() const
		{
			return ((Second - First) * (Third - First)).Direction();
		}

		//void ConvertToBarycentric(Vector3& p_Point)
		//{
		//	const Vector3 triangleNormal = (Second - First) * (Third - First);

		//	const scalar normedX = AbsoluteValue(triangleNormal(0));
		//	const scalar normedY = AbsoluteValue(triangleNormal(1));
		//	const scalar normedZ = AbsoluteValue(triangleNormal(2));

		//	if (normedX >= normedY && normedX >= normedZ)
		//	{
		//		//ConvertToBarycentric(triangleNormal(0), std::function<void(const scalar, const Vector3&, scalar&, scalar&, scalar&)>(ProjOnYZ), p_Point);
		//	}
		//	else if (normedY >= normedX && normedY >= normedZ)
		//	{
		//		//ConvertToBarycentric(triangleNormal(1), std::function<void(const scalar, const Vector3&, scalar&, scalar&, scalar&)>(ProjOnXZ), p_Point);
		//	}
		//	else
		//	{
		//		//ConvertToBarycentric(triangleNormal(2), ProjOnXY, p_Point);
		//	}

		//}

	private:

		//void ProjOnYZ(const scalar p_NormComp, const Vector3& p_Point, scalar& p_InvNormComp, scalar& p_NormedU, scalar& p_NormedV)
		//{
		//	p_NormedU = SignedTriangularArea(MakeVector(p_Point(1), p_Point(2))
		//		, MakeVector(Second(1), Second(2))
		//		, MakeVector(Third(1), Third(2)));
		//	p_NormedV = SignedTriangularArea(MakeVector(p_Point(1), p_Point(2))
		//		, MakeVector(Third(1), Third(2))
		//		, MakeVector(First(1), First(2)));
		//	p_InvNormComp = Unity / p_NormComp;
		//}
		//void ProjOnXZ(const scalar p_NormComp, const Vector3& p_Point, scalar& p_InvNormComp, scalar& p_NormedU, scalar& p_NormedV)
		//{
		//	p_NormedU = SignedTriangularArea(MakeVector(p_Point(0), p_Point(2))
		//		, MakeVector(Second(0), Second(2))
		//		, MakeVector(Third(0), Third(2)));
		//	p_NormedV = SignedTriangularArea(MakeVector(p_Point(0), p_Point(2))
		//		, MakeVector(Third(0), Third(2))
		//		, MakeVector(First(0), First(2)));
		//	p_InvNormComp = Unity / -p_NormComp;
		//}
		//void ProjOnXY(const scalar p_NormComp, const Vector3& p_Point, scalar& p_InvNormComp, scalar& p_NormedU, scalar& p_NormedV)
		//{
		//	p_NormedU = SignedTriangularArea(MakeVector(p_Point(0), p_Point(1))
		//		, MakeVector(Second(0), Second(1))
		//		, MakeVector(Third(0), Third(1)));
		//	p_NormedV = SignedTriangularArea(MakeVector(p_Point(0), p_Point(1))
		//		, MakeVector(Third(0), Third(1))
		//		, MakeVector(First(0), First(1)));
		//	p_InvNormComp = Unity / p_NormComp;
		//}

		//void ConvertToBarycentric(const scalar p_NormComp, std::function<void(const scalar, const Vector3&, scalar&, scalar&, scalar&)> m_NormFxn, Vector3& p_Point)
		//{
		//	scalar invNormComp, normU, normV;
		//	m_NormFxn(p_NormComp, p_Point, invNormComp, normU, normV);
		//	p_Point(0) = normU * invNormComp;
		//	p_Point(1) = normV * invNormComp;
		//	p_Point(2) = Unity - p_Point(0) - p_Point(1);
		//}

	//Attributes
	public:

		Vector3 First;
		Vector3 Second;
		Vector3 Third;
	};

	typedef Triangle<2> Triangle2;
	typedef Triangle<3> Triangle3;
	//typedef Triangle<4> Triangle4;

	//===========================================================================
	// Functions
	//===========================================================================

} // namespace Mathematics

#endif //#ifndef IncludedMathTriangleH