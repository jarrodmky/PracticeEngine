#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Synchronization/Encoding.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{
	TEST_CLASS(DeleteTest)
	{
	public:

		TEST_METHOD(EndianTest)
		{
			Assert::IsTrue(LittleEndian() ^ BigEndian());
		}
		
		TEST_METHOD(MacroTest)
		{
			int* tester = new int;

			Assert::IsNotNull(tester);

			ProperlyDelete(tester);
		}
		
		TEST_METHOD(EncodeTest)
		{
			Base64Coder coder;


			const char* binaryInput = "Man is distinguished, not only by his reason, but by this singular passion from "
							"other animals, which is a lust of the mind, that by a perseverance of delight "
							"in the continued and indefatigable generation of knowledge, exceeds the short "
							"vehemence of any carnal pleasure.";
			u32 length = strlen(binaryInput);
			std::string outString;
			coder.Encode((u8*)binaryInput, length, outString);

			Assert::IsTrue(strcmp(outString.c_str(), "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz"
"IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"
"dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu"
"dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
"ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=") == 0);

			
			binaryInput = "M";
			length = strlen(binaryInput);
			outString.clear();
			coder.Encode((u8*)binaryInput, length, outString);

			Assert::IsTrue(strcmp(outString.c_str(), "TQ==") == 0);
		}
	};
}