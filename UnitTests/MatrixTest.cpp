#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mathematics;

namespace MathematicsTest
{		
	TEST_CLASS(VectorTest)
	{
	public:
		
		TEST_METHOD(VectorConstruction)
		{
			Vector a(ConstantVectors::Zero);
			Assert::IsTrue(a.x == ConstantScalars::Zero);
			Assert::IsTrue(a.y == ConstantScalars::Zero);
			Assert::IsTrue(a.z == ConstantScalars::Zero);
		}

		TEST_METHOD(CrossProduct)
		{
			Vector a(40.0f, 120.0f, 630.0f);
			Vector b(100.0f, 30.0f, 50.0f);
			Vector c(a * b);

			Assert::IsTrue(EquivalentToZero(a|c));
			Assert::IsTrue(EquivalentToZero(b|c));
		}
	};
}