#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Abstracts;

namespace UnitTests
{
	TEST_CLASS(AbstractTest)
	{
	public:
		
		TEST_METHOD(ListTest)
		{
			List<u32> tester;

			tester.Add(128);
			tester.Add(64);
			
			u32 getter = -1;

			tester.Peek(0, getter);
			Assert::AreNotEqual(getter, u32(-1));

			Assert::AreEqual(getter, u32(128));

			tester.Peek(1, getter);
			Assert::AreEqual(getter, u32(64));


		}

	};
}