#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{
	TEST_CLASS(LogTest)
	{
	public:

		TEST_METHOD(TestNoParam)
		{
			Log("");
		}
		
		TEST_METHOD(TestIntParam)
		{
			const char* secretMessage = "Testing...Testing...";

			Log(secretMessage);
		}

		TEST_METHOD(TestStringParam)
		{
			const char* longMessage = "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"\
				"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"\
				"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"\
				"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"\
				"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"\
				"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"\
				"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"\
				"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"\
				"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
			Log("%s", longMessage);
		}

		TEST_METHOD(TestLongParam)
		{
			Log("Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro."\
				"Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro."\
				"Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro."\
				"Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro."\
				"Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro."\
				"Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro."\
				"Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro.Testing the logging macro.");
		}

	};
}