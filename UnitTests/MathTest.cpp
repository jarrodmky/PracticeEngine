#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Mathematics;

namespace UnitTests
{
	TEST_CLASS(MathTest)
	{
	public:
		
		TEST_METHOD(VectorConstruction)
		{
			Vector a(ConstantVectors::Zero);
			Assert::IsTrue(a.x == ConstantScalars::Zero);
			Assert::IsTrue(a.y == ConstantScalars::Zero);
			Assert::IsTrue(a.z == ConstantScalars::Zero);
		}

		TEST_METHOD(VectorLength)
		{
			Vector a(1.0f, -231232.0f, 355675.0f);
			Vector b(-1.0f, 231232.0f, -355675.0f);

			Assert::IsTrue(ApproximateToEachOther(a.Direction().Length(), 1.0f, 0.00000012f));
			Assert::IsTrue(a.Direction() == -(b.Direction()));
		}

		TEST_METHOD(VectorDotProduct)
		{
			Vector a(10000.0f, 0.0f, 0.0f);
			Vector b(0.0f, 1.0f, 1.0f);
			
			Assert::IsTrue(ApproximateToEachOther(a|b, a.Length() * b.Length() * std::cos(ConstantScalars::PiOverTwo), 0.00065f));
			Assert::IsTrue(ApproximateToEachOther(a|b, a.Length() * b.Length() * std::cos(AngleBetween(a, b)), 0.00065f));
		}

		TEST_METHOD(VectorCrossProduct)
		{
			Vector a(4.0f, 124530.0f, 630.0f);
			Vector b(103450.0f, 30.0f, 534540.0f);
			Vector c(a * b);

			Assert::IsTrue(EquivalentToEachOther(a|c, 0.0f));
			Assert::IsTrue(EquivalentToEachOther(b|c, 0.0f));
		}

		TEST_METHOD(MatrixMultiplication)
		{
			Matrix A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
			Matrix B(23.0f, 19.0f, 17.0f, 13.0f, 11.0f, 7.0f, 5.0f, 3.0f, 2.0f);

			Matrix C(A*B);
			
			Assert::IsTrue(C == Matrix(64.0f, 50.0f, 37.0f, 187.0f, 149.0f, 115.0f, 310.0f, 248.0f, 193.0f));
		}

		TEST_METHOD(MatrixInverse)
		{
			Matrix A(1.0f, 2.0f, 3.0f, 4.0f
				   , 5.0f, 6.0f, 7.0f, 8.0f
				   , 9.0f, 10.0f, 11.0f, 12.0f
				   , 13.0f, 14.0f, 15.0f, 16.0f);
			//Matrix B(A.Inverse());

			//Matrix C(A*B);
			
			//Assert::IsTrue(C == ConstantMatrices::Identity);
		}

		TEST_METHOD(MatrixRotation)
		{
			scalar theta(ConstantScalars::PiSquared);
			scalar right(ConstantScalars::PiOverTwo);
			Vector test(344.0f, 214563.0f, 2.0f);

			Vector rotX_1(Rotation(ConstantVectors::I, theta) * test);
			Vector rotX_2(RotationAboutX(theta) * test);
			Assert::IsTrue(ApproximateToEachOther(rotX_1, rotX_2, 0.000035f));
			
			Vector rotY_1(Rotation(ConstantVectors::J, theta) * test);
			Vector rotY_2(RotationAboutY(theta) * test);
			Assert::IsTrue(ApproximateToEachOther(rotY_1, rotY_2, 0.02f));
			
			Vector rotZ_1(Rotation(ConstantVectors::K, theta) * test);
			Vector rotZ_2(RotationAboutZ(theta) * test);
			Assert::IsTrue(ApproximateToEachOther(rotZ_1, rotZ_2, 0.0000002f));
		}
	};
}