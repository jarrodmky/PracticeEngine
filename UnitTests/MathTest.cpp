#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Mathematics;

static const u32 testIts = 1000;

namespace UnitTests
{
	TEST_CLASS(MathTest)
	{
	public:

		TEST_METHOD(VectorConstruction)
		{
			Vector3 a(Zero);
			Assert::IsTrue(a(0) == Zero);
			Assert::IsTrue(a(1) == Zero);
			Assert::IsTrue(a(2) == Zero);
		}

		TEST_METHOD(VectorLength)
		{
			Random::Initialize();
			const scalar tau = 0.01f;

			for (u32 i = 0; i < testIts; ++i)
			{
				Vector3 a(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 b(-a);

				Assert::IsTrue(IsApproximatelyUnity(a.Direction().Length(), 0.00000012f));
				Assert::IsTrue(IsApproximatelyUnity(b.Direction().Length(), 0.00000012f));

				Assert::IsTrue(a == a.Length() * a.Direction());
				Assert::IsTrue(b == b.Length() * b.Direction());

				Assert::IsTrue(a.Length() == b.Length());
				Assert::IsTrue(a.Direction() == -(b.Direction()));
			}
		}

		TEST_METHOD(VectorDotProduct)
		{
			Random::Initialize();
			const scalar tau = 0.01f;

			for (u32 i = 0; i < testIts; ++i)
			{

				Vector3 a(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 b(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 c(MakeRandomVector3(-100.0f, 100.0f));
				const scalar r = MakeRandomScalar(-100.0f, 100.0f);

				Assert::IsTrue(IsEqualTo(a | b, b | a));
				Assert::IsTrue(IsEqualTo(a | a, a.LengthSquared()));

				Assert::IsTrue(IsApproximatelyEqualTo((r * a) | b, a | (r * b), tau));
				Assert::IsTrue(IsApproximatelyEqualTo((r * a) | b, r * (a | b), tau));

				Assert::IsTrue(IsApproximatelyEqualTo(a | (b + c), (a | b) + (a | c), tau));

				Assert::IsTrue(IsApproximatelyEqualTo(a.Length() * b.Length() * std::cos(AngleBetween(a, b)), a | b, tau));
			}
		}

		TEST_METHOD(VectorCrossProduct)
		{
			Random::Initialize();
			const scalar tolerance = 0.01f;

			for (u32 i = 0; i < testIts; ++i)
			{
				Vector3 a(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 b(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 c(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 d(MakeRandomVector3(-100.0f, 100.0f));
				const scalar r = MakeRandomScalar(-100.0f, 100.0f);
				Vector3 abCross(a * b);

				Assert::IsTrue(a * a == Zero3());

				Assert::IsTrue(IsApproximatelyZero(a | abCross, 1.0f));
				Assert::IsTrue(IsApproximatelyZero(b | abCross, 1.0f));

				Assert::IsTrue(ApproximatelyEqual((r * a) * b, a * (r * b), tolerance));
				Assert::IsTrue(ApproximatelyEqual(r * (a * b), a * (r * b), tolerance));
				Assert::IsTrue(ApproximatelyEqual(a * (b + c), (a * b) + (a * c), tolerance));

				Assert::IsTrue(IsApproximatelyEqualTo((a * b) | c, (c * a) | b, tolerance));
				Assert::IsTrue(IsApproximatelyEqualTo((c * a) | b, (b * c) | a, tolerance));
				Assert::IsTrue(b * a == -abCross);

				//lagranges identity
				Assert::IsTrue(IsApproximatelyEqualTo((a * b) | (c * d), (a | c) * (b | d) - (b | c) * (a | d), tolerance));

				//jacobis identity
				Assert::IsTrue(ApproximatelyEqual(a * (b * c) + b * (c * a) + c * (a * b), Zero3(), 1.0f));

				Assert::IsTrue(ApproximatelyEqual(a * (b * a), a * b * a, tolerance));
				Assert::IsTrue(ApproximatelyEqual((a * b) * a, a * b * a, tolerance));
				Assert::IsTrue(ApproximatelyEqual(a * b * a, a.LengthSquared() * b - (a | b) * a, tolerance));
			}
		}

		TEST_METHOD(VectorProjections)
		{
			Random::Initialize();
			const scalar tau(0.0001f);

			for (u32 i = 0; i < testIts; ++i)
			{
				Vector3 v(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 n(MakeRandomVector3(-100.0f, 100.0f).Direction());

				Vector4 V(MakeAffineVector(MakeRandomVector3(-100.0f, 100.0f)));
				Vector4 N(MakeAffineVector(MakeRandomVector3(-100.0f, 100.0f)).Direction());

				scalar a(MakeRandomScalar(-100.0f, 100.0f));

				//3d
				Assert::IsTrue(v.LengthAlong(n) == (n | v));
				Assert::IsTrue(v.ProjectionAlong(n) == n * (n | v));
				Assert::IsTrue(ApproximatelyEqual(v.RejectionFrom(n), v - n * (n | v), tau));

				//4d
				Assert::IsTrue(V.LengthAlong(N) == (N | V));
				Assert::IsTrue(V.ProjectionAlong(N) == N * (N | V));
				Assert::IsTrue(ApproximatelyEqual(V.RejectionFrom(N), V - N * (N | V), tau));

				//3d functions
				if (Parallel(v, n))
				{
					continue;
				}

				//rotated vector function
				Assert::IsTrue(ApproximatelyEqual(RotatedVector(n, a, v)
					, v.ProjectionAlong(n) + v.RejectionFrom(n) * std::cos(a) + (v * n) * std::sin(a), tau));
				Assert::IsTrue(ApproximatelyEqual(RotatedVector(n, a, v)
					, n*(n | v) + (v - n*(n | v)) * std::cos(a) + (v * n) * std::sin(a), tau));

				//projected vector function
				Assert::IsTrue(ApproximatelyEqual(ProjectedVector(n, v), v.ProjectionAlong(n), tau));
				Assert::IsTrue(ApproximatelyEqual(ProjectedVector(n, v)
					, n*(n | v), tau));
			}
		}

		TEST_METHOD(TripleProducts)
		{
			Random::Initialize();
			const scalar tolerance = 1.0f;

			for (u32 i = 0; i < testIts; ++i)
			{
				Vector3 u(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 v(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 w(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 x(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 y(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 z(MakeRandomVector3(-100.0f, 100.0f));

				Assert::IsTrue(IsApproximatelyEqualTo(ScalarTripleProduct(v, w, u), ScalarTripleProduct(u, v, w), tolerance));
				Assert::IsTrue(IsApproximatelyEqualTo(ScalarTripleProduct(w, u, v), ScalarTripleProduct(u, v, w), tolerance));
				Assert::IsTrue(IsApproximatelyEqualTo(-ScalarTripleProduct(u, w, v), ScalarTripleProduct(u, v, w), tolerance));
				Assert::IsTrue(IsApproximatelyEqualTo(-ScalarTripleProduct(v, u, w), ScalarTripleProduct(u, v, w), tolerance));
				Assert::IsTrue(IsApproximatelyEqualTo(-ScalarTripleProduct(w, v, u), ScalarTripleProduct(u, v, w), tolerance));

				Assert::IsTrue(IsApproximatelyZero(ScalarTripleProduct(u, u, v), 1.0f));
				Assert::IsTrue(IsApproximatelyZero(ScalarTripleProduct(v, u, v), 1.0f));

				Assert::IsTrue(IsApproximatelyEqualTo(ScalarTripleProduct(u, v, w) * ScalarTripleProduct(u, v, w), ScalarTripleProduct(u * v, v * w, w * u), tolerance));
				Assert::IsTrue(IsApproximatelyEqualTo(ScalarTripleProduct(u + v, v + w, w + u), 2.0f * ScalarTripleProduct(u, v, w), tolerance));
				Assert::IsTrue(IsApproximatelyEqualTo(ScalarTripleProduct(u, v, w) * ScalarTripleProduct(x, y, z), MakeMatrix(u | x, u | y, u | z, v | x, v | y, v | z, w | x, w | y, w | z).Determinant(), tolerance));
			}
		}

		TEST_METHOD(MatrixAddition)
		{
			Random::Initialize();
			const scalar tau = 0.01f;

			for (u32 i = 0; i < testIts; ++i)
			{
				Matrix44 A(MakeRandomMatrix44(-100.0f, 100.0f));
				Matrix44 B(MakeRandomMatrix44(-100.0f, 100.0f));
				Matrix44 C(MakeRandomMatrix44(-100.0f, 100.0f));
				scalar a(MakeRandomScalar(-100.0f, 100.0f));
				scalar b(MakeRandomScalar(-100.0f, 100.0f));

				Assert::IsTrue(A + B == B + A);
				Assert::IsTrue(ApproximatelyEqual((A + B) + C, A + (B + C), tau));
				Assert::IsTrue(ApproximatelyEqual(a*(b*A), (a*b)*A, tau));
				Assert::IsTrue(ApproximatelyEqual(a*(A + B), a * A + a * B, tau));
				Assert::IsTrue(ApproximatelyEqual((a + b) * A, a * A + b * A, tau));
			}
		}

		TEST_METHOD(MatrixMultiplication)
		{
			Random::Initialize();
			const scalar tau = 0.1f;

			for (u32 i = 0; i < testIts; ++i)
			{
				Matrix44 A(MakeRandomMatrix44(-100.0f, 100.0f));
				Matrix44 B(MakeRandomMatrix44(-100.0f, 100.0f));
				Matrix44 C(MakeRandomMatrix44(-100.0f, 100.0f));
				scalar a(MakeRandomScalar(-100.0f, 100.0f));

				Assert::IsTrue(ApproximatelyEqual((a*A)*B, a*(A*B), tau));
				Assert::IsTrue(ApproximatelyEqual((A*B)*C, A*(B*C), tau));
				Assert::IsTrue((A*B).Transposition() == B.Transposition()*A.Transposition());
				Assert::IsTrue((A + B).Transposition() == A.Transposition() + B.Transposition());
				Assert::IsTrue((A - B).Transposition() == A.Transposition() - B.Transposition());
				Assert::IsTrue((a * A).Transposition() == a * A.Transposition());
			}
		}

		TEST_METHOD(MatrixInverse)
		{
			Random::Initialize();
			const scalar tau = 1.0f;

			for (u32 i = 0; i < testIts; ++i)
			{
				//check for diagonal matrix
				scalar s(MakeRandomScalar(-100.0f, 100.0f));
				scalar t(MakeRandomScalar(-100.0f, 100.0f));
				scalar u(MakeRandomScalar(-100.0f, 100.0f));

				Matrix33 CheckDiags(MakeMatrix(s, Zero, Zero, Zero, t, Zero, Zero, Zero, u));
				Assert::IsTrue(!CheckDiags.IsSingular());
				Assert::IsTrue(IsEqualTo(CheckDiags.Determinant(), s*t*u));

				//check for determinant
				Vector3 v1(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 v2(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 v3(MakeRandomVector3(-100.0f, 100.0f));

				Matrix33 CheckDet(MakeMatrix(v1, v2, v3));
				Assert::IsTrue(IsApproximatelyEqualTo(CheckDet.Determinant(), v1 | (v2 * v3), tau));

				Matrix33 CheckDups(MakeMatrix(v1, v2, v2));
				Assert::IsTrue(CheckDups.IsSingular());

				Matrix33 CheckZero1(MakeMatrix(Zero3(), v2, v3));
				Matrix33 CheckZero2(MakeMatrix(v1, Zero3(), v3));
				Matrix33 CheckZero3(MakeMatrix(v1, v2, Zero3()));
				Assert::IsTrue(CheckZero1.IsSingular() && CheckZero2.IsSingular() && CheckZero3.IsSingular());

				//elementary row ops
				Matrix44 M(MakeRandomMatrix44(-100.0f, 100.0f));
				scalar r(MakeRandomScalar(-100.0f, 100.0f));
				scalar m(M.Determinant());
				
				M.SwitchRows(1, 2);
				Assert::IsTrue(IsApproximatelyEqualTo(M.Determinant(), -m, tau));
				m = M.Determinant();

				M.ScaleRow(3, r);
				Assert::IsTrue(IsApproximatelyEqualTo(M.Determinant(), r*m, tau));
				m = M.Determinant();

				M.AddScaledRowToRow(0, 3, r);
				Assert::IsTrue(IsApproximatelyEqualTo(M.Determinant(), m, tau));

				//linear system
				Matrix44 A(MakeRandomMatrix44(-100.0f, 100.0f));
				Vector4 x(MakeRandomVector4(-100.0f, 100.0f));
				Matrix44 xSet(MakeRandomMatrix44(-100.0f, 100.0f));
				Vector4 b(A * x);
				Matrix44 bSet(A * xSet);
				Vector4 sol;
				Matrix44 solSet;

				SolveLinearSystem(A, b, sol);
				Assert::IsTrue(ApproximatelyEqual(sol, x, 0.1f));

				SolveLinearSystems(A, bSet, solSet);
				Assert::IsTrue(ApproximatelyEqual(solSet, xSet, 1.0f));

				//properties of determinant
				Matrix44 B(MakeRandomMatrix44(-100.0f, 100.0f));

				//check for arbitrary closeness for comparison
				Assert::IsTrue(Close(A, B, 1000000.0f));

				Assert::IsTrue(ApproximatelyEqual(A.Transposition().Determinant(), A.Determinant(), 100.0f));

				Assert::IsTrue(ApproximatelyEqual(A.Determinant() * B.Determinant(), (A*B).Determinant(), 0.01f));
				
				//properties of inverse
				Assert::IsTrue(A.IsSingular() || ApproximatelyEqual(A.Inverse() * A, A.Inverse() * A, 0.0000000001f));
				Assert::IsTrue(A.IsSingular() || ApproximatelyEqual(A.Inverse() * A, I4(), 0.01f));
				Assert::IsTrue(A.IsSingular() || ApproximatelyEqual(A.Inverse().Determinant(), Inverse(A.Determinant()), 0.0001f));
				

				if (!A.IsSingular() && !B.IsSingular())
				{
					Assert::IsTrue(ApproximatelyEqual(A.Inverse() * B.Inverse(), (B*A).Inverse(), 0.01f));
				}
			}
		}

		TEST_METHOD(TransformationMatrices)
		{
			Random::Initialize();
			const scalar tau(0.001f);

			for (u32 i = 0; i < testIts; ++i)
			{
				Vector3 translation(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 axis(MakeRandomVector3(-100.0f, 100.0f).Direction());
				scalar angle(MakeRandomScalar(Zero, TwoPi));
				scalar uniScaling(MakeRandomScalar(-100.0f, 100.0f));
				Vector3 scaling(MakeRandomVector3(-100.0f, 100.0f));

				Matrix44 T(MakeTranslation(translation));
				Matrix44 R(MakeRotation(axis, angle));
				Matrix44 S(MakeScaling(scaling));

				//transforms and inverses
				Assert::IsTrue(ApproximatelyEqual(R.Inverse(), MakeInverseRotation(axis, angle), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeRotationAboutX(angle).Inverse(), MakeInverseRotation(I(), angle), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeRotationAboutY(angle).Inverse(), MakeInverseRotation(J(), angle), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeRotationAboutZ(angle).Inverse(), MakeInverseRotation(K(), angle), tau));

				Assert::IsTrue(T.Inverse() == MakeInverseTranslation(translation));
				Assert::IsTrue(MakeScaling(uniScaling).Inverse() == MakeInverseScaling(uniScaling));
				Assert::IsTrue(MakeScaling(uniScaling) == MakeScaling(Vector3(uniScaling)));
				Assert::IsTrue(MakeScaling(scaling).Inverse() == MakeInverseScaling(scaling));

				//vectors and points
				Vector4 V(MakeAffineVector(MakeRandomVector3(-100.0f, 100.0f)));
				Vector3 p(MakeRandomVector3(-100.0f, 100.0f));
				Vector4 P(MakeAffinePoint(p));
				Vector4 A(MakeAffineVector(axis));

				Assert::IsTrue(T * V == V);
				Assert::IsTrue(ApproximatelyEqual(S * V, V % MakeAffineVector(scaling), tau));
				Assert::IsTrue(ApproximatelyEqual(R * V, V.RejectionFrom(A) * std::cos(angle) + (A * V) * std::sin(angle) + V.ProjectionAlong(A), tau));

				Assert::IsTrue(T * P == P + MakeAffineVector(translation));
				Assert::IsTrue(ApproximatelyEqual(S * P, MakeAffinePoint(p % scaling), tau));
				Assert::IsTrue(ApproximatelyEqual(R * P, MakeAffinePoint(p.RejectionFrom(axis) * std::cos(angle) + (axis * p) * std::sin(angle) + p.ProjectionAlong(axis)), tau));


			}
		}

		TEST_METHOD(FrameTransform)
		{
			Random::Initialize();
			const scalar tau(0.001f);

			for (u32 i = 0; i < testIts; ++i)
			{
				scalar r(MakeRandomScalar(-100.0f, 100.0f));
				scalar p(MakeRandomScalar(-100.0f, 100.0f));
				scalar y(MakeRandomScalar(-100.0f, 100.0f));

				//rotation
				Frame Roller;
				Frame Pitcher;
				Frame Yawer;
				Roller.Roll(r);
				Pitcher.Pitch(p);
				Yawer.Yaw(y);

				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Roller.GetUp()), MakeRotation(-K(), r) * Y(), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Roller.GetRight()), MakeRotation(-K(), r) * X(), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Roller.GetForward()), -Z(), tau));

				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Pitcher.GetUp()), MakeRotation(I(), p) * Y(), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Pitcher.GetRight()), X(), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Pitcher.GetForward()), MakeRotation(I(), p) * -Z(), tau));

				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Yawer.GetUp()), Y(), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Yawer.GetRight()), MakeRotation(J(), y) * X(), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeAffineVector(Yawer.GetForward()), MakeRotation(J(), y) * -Z(), tau));
			}
		}

		TEST_METHOD(QuaternionMath)
		{
			Random::Initialize();
			const scalar tau(0.01f);

			for (u32 i = 0; i < testIts; ++i)
			{
				Vector3 axis(MakeRandomVector3(-100.0f, 100.0f).Direction());
				scalar angle(MakeRandomScalar(-100.0f, 100.0f));
				Quaternion q1(axis, angle);
				Quaternion q2(MakeRandomVector3(-100.0f, 100.0f).Direction(), MakeRandomScalar(-100.0f, 100.0f));

				Assert::IsTrue(ApproximatelyEqual(MakeRotation(axis, angle), MakeRotation(q1), tau));
				Assert::IsTrue(ApproximatelyEqual(MakeRotation(q1).Inverse(), MakeInverseRotation(q1), tau));

				Vector4 q1AsV(MakeVector(q1.Real(), q1.Imaginary()(0), q1.Imaginary()(1), q1.Imaginary()(2)));
				Vector4 q2AsV(MakeVector(q2.Real(), q2.Imaginary()(0), q2.Imaginary()(1), q2.Imaginary()(2)));

				Assert::IsTrue(IsApproximatelyEqualTo((q1 | q2), (q1AsV | q2AsV), tau));
				Assert::IsTrue(ApproximatelyEqual(q1 * q2, Quaternion(q1.ScalarPart() * q2.ScalarPart() - (q1.VectorPart() | q2.VectorPart())
					, q1.ScalarPart() * q2.VectorPart() + q2.ScalarPart() * q1.VectorPart() + q1.VectorPart() * q2.VectorPart()), 0.0000000001f));

				Vector3 v1(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 v2(v1);

				q1.Rotate(v1);
				q2.Rotate(v1);

				(q2 * q1).Rotate(v2);

				Assert::IsTrue(ApproximatelyEqual(v1, v2, tau));
				Assert::IsTrue((q1 * q1.Conjugation()).IsScalar());
				Assert::IsTrue(Equal((q1 * q1.Conjugation()).ScalarPart(), q1.LengthSquared()));
				Assert::IsTrue((q1 * q1.Inverse()).IsScalar());
				Assert::IsTrue(IsUnity((q1 * q1.Inverse()).ScalarPart()));



				Vector3 u(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 v(MakeRandomVector3(-100.0f, 100.0f));
				Vector3 uRotated(RotatedVector(axis, angle, u));
				Vector3 vRotated(RotatedVector(axis, angle, v));
				Assert::IsTrue(ApproximatelyEqual(u.Length(), uRotated.Length(), tau));
				Assert::IsTrue(ApproximatelyEqual(uRotated | vRotated, u | v, tau));
				Assert::IsTrue(ApproximatelyEqual(uRotated * vRotated, RotatedVector(axis, angle, u * v), tau));
			}
		}


		TEST_METHOD(SeriesTest)
		{

			Assert::IsTrue(Combinations<0, 0>::Integer() == 1);

			Assert::IsTrue(Combinations<1, 0>::Integer() == 1);
			Assert::IsTrue(Combinations<1, 1>::Integer() == 1);

			Assert::IsTrue(Combinations<2, 0>::Integer() == 1);
			Assert::IsTrue(Combinations<2, 1>::Integer() == 2);
			Assert::IsTrue(Combinations<2, 2>::Integer() == 1);

			Assert::IsTrue(Combinations<3, 0>::Integer() == 1);
			Assert::IsTrue(Combinations<3, 1>::Integer() == 3);
			Assert::IsTrue(Combinations<3, 2>::Integer() == 3);
			Assert::IsTrue(Combinations<3, 3>::Integer() == 1);

			Assert::IsTrue(Combinations<4, 0>::Integer() == 1);
			Assert::IsTrue(Combinations<4, 1>::Integer() == 4);
			Assert::IsTrue(Combinations<4, 2>::Integer() == 6);
			Assert::IsTrue(Combinations<4, 3>::Integer() == 4);
			Assert::IsTrue(Combinations<4, 4>::Integer() == 1);

			Assert::IsTrue(Combinations<5, 0>::Integer() == 1);
			Assert::IsTrue(Combinations<5, 1>::Integer() == 5);
			Assert::IsTrue(Combinations<5, 2>::Integer() == 10);
			Assert::IsTrue(Combinations<5, 3>::Integer() == 10);
			Assert::IsTrue(Combinations<5, 4>::Integer() == 5);
			Assert::IsTrue(Combinations<5, 5>::Integer() == 1); 

			Assert::IsTrue(Triangular<0>::Integer() == 0);
			Assert::IsTrue(Triangular<1>::Integer() == 1);
			Assert::IsTrue(Triangular<2>::Integer() == 3);
			Assert::IsTrue(Triangular<3>::Integer() == 6);
			Assert::IsTrue(Triangular<4>::Integer() == 10);
			Assert::IsTrue(Triangular<5>::Integer() == 15);
			Assert::IsTrue(Triangular<6>::Integer() == 21);

			Assert::IsTrue(Factorial<0>::Integer() == 1);
			Assert::IsTrue(Factorial<1>::Integer() == 1);
			Assert::IsTrue(Factorial<2>::Integer() == 2);
			Assert::IsTrue(Factorial<3>::Integer() == 6);
			Assert::IsTrue(Factorial<4>::Integer() == 24);
			Assert::IsTrue(Factorial<5>::Integer() == 120);
			Assert::IsTrue(Factorial<6>::Integer() == 720);

			Assert::IsTrue(Fibonacci<0>::Integer() == 0);
			Assert::IsTrue(Fibonacci<1>::Integer() == 1);
			Assert::IsTrue(Fibonacci<2>::Integer() == 1);
			Assert::IsTrue(Fibonacci<3>::Integer() == 2);
			Assert::IsTrue(Fibonacci<4>::Integer() == 3);
			Assert::IsTrue(Fibonacci<5>::Integer() == 5);
			Assert::IsTrue(Fibonacci<6>::Integer() == 8);

		}

		TEST_METHOD(PolynomialMath)
		{
			Random::Initialize();
			const scalar tau(0.0001f);

			Quadratic product = MakePolynomial(1, 5) * MakePolynomial(1, -2);
			Assert::IsTrue(product == MakePolynomial(1, 3, -10));

//			Cubic product2 = MakePolynomial(1, 1, 1) * MakePolynomial(1, -2);
	//		Assert::IsTrue(product2 == MakePolynomial(1, -1, -1, -2));

			Cubic uno = Cubic(Ones4());
			Assert::IsTrue(IsApproximatelyEqualTo(uno.Derivative()(Unity), (scalar)Triangular<2>::Float(), tau));

			for (u32 i = 0; i < testIts; ++i)
			{
				const scalar a(MakeRandomScalar(-10.0f, 10.0f));
				const scalar b(MakeRandomScalar(-10.0f, 10.0f));
				const scalar c(MakeRandomScalar(-10.0f, 10.0f));
				const scalar d(MakeRandomScalar(-10.0f, 10.0f));

				const Matrix33 A(MakeRandomMatrix33(-10.0f, 10.0f));

				Cubic P = MakePolynomial(a, b, c, Zero);
				Assert::IsTrue(IsZero(P(Zero)));

				Cubic Q = MakePolynomial(a, b, c, d);
				Assert::IsTrue(IsApproximatelyEqualTo(Q(Unity), a + b + c + d, tau));


			}
		}

	};
}