#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{
	TEST_CLASS(DeleteTest)
	{
	public:
		
		TEST_METHOD(TestProperlyDelete)
		{
			int* tester = new int;

			Assert::IsNotNull(tester);

			ProperlyDelete(tester);

			Assert::IsNull(tester);
		}

	};
}