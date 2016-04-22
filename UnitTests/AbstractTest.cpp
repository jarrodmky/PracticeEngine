#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Abstracts;

namespace UnitTests
{
	TEST_CLASS(AbstractTest)
	{
	public:

		TEST_METHOD(ArrayTest)
		{
			//initialization
			int oneInt = -2;
			int alottaInts[64] =
			{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
			, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
			, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29
			, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
			, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49
			, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59
			, 60, 61, 62, 63 };

			Array<int, 64> A(oneInt);
			Array<int, 64> B(alottaInts, 64);
			for (u32 i = 0; i < 64; ++i)
			{
				Assert::IsTrue(A[i] == oneInt);
				Assert::IsTrue(B[i] == alottaInts[i]);
			}

			Array<int, 8, 8> C(oneInt);
			Array<int, 8, 8> D(alottaInts, 64);
			for (u32 i = 0; i < 8; ++i)
			{

				for (u32 j = 0; j < 8; ++j)
				{
					Assert::IsTrue(C(i, j) == oneInt);
					Assert::IsTrue(D(i, j) == alottaInts[8 * j + i]);
				}
			}


			Array<int, 4, 4, 4> E(oneInt);
			Array<int, 4, 4, 4> F(alottaInts, 64);
			for (u32 i = 0; i < 4; ++i)
			{
				for (u32 j = 0; j < 4; ++j)
				{
					for (u32 k = 0; k < 4; ++k)
					{
						Assert::IsTrue(E(i, j, k) == oneInt);
						Assert::IsTrue(F(i, j, k) == alottaInts[16 * k + 4 * j + i]);
					}
				}
			}

			//copy ctor
			Array<int, 64> copy1d(B);
			Array<int, 8, 8> copy2d(D);
			Array<int, 4, 4, 4> copy3d(F);

			//fill in and equals
			copy1d.Clear(oneInt);
			Assert::IsTrue(A == copy1d);
			for (u32 i = 0; i < 64; ++i)
			{
				Assert::IsTrue(A[i] == copy1d[i]);
			}

			copy2d.Clear(oneInt);
			Assert::IsTrue(C == copy2d);
			for (u32 i = 0; i < 8; ++i)
			{
				for (u32 j = 0; j < 8; ++j)
				{
					Assert::IsTrue(C(i, j) == copy2d(i, j));
				}
			}

			copy3d.Clear(oneInt);
			Assert::IsTrue(E == copy3d);
			for (u32 i = 0; i < 4; ++i)
			{
				for (u32 j = 0; j < 4; ++j)
				{
					for (u32 k = 0; k < 4; ++k)
					{
						Assert::IsTrue(E(i, j, k) == copy3d(i, j, k));
					}
				}
			}

			
			//should be same as the beginning

			for (u32 i = 0; i < 64; ++i)
			{
				Assert::IsTrue(A[i] == oneInt);
				Assert::IsTrue(B[i] == alottaInts[i]);
			}

			for (u32 i = 0; i < 8; ++i)
			{

				for (u32 j = 0; j < 8; ++j)
				{
					Assert::IsTrue(C(i, j) == oneInt);
					Assert::IsTrue(D(i, j) == alottaInts[8 * j + i]);
				}
			}

			for (u32 i = 0; i < 4; ++i)
			{
				for (u32 j = 0; j < 4; ++j)
				{
					for (u32 k = 0; k < 4; ++k)
					{
						Assert::IsTrue(E(i, j, k) == oneInt);
						Assert::IsTrue(F(i, j, k) == alottaInts[16 * k + 4 * j + i]);
					}
				}
			}
		}

		TEST_METHOD(DynamicArrayTest)
		{
			//initialization
			int oneInt = -2;
			int alottaInts[64] =
			{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
			, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
			, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29
			, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
			, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49
			, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59
			, 60, 61, 62, 63 };


			DynamicArray<int> A(oneInt, 64);
			DynamicArray<int> B(1, 64);
			B.Store(alottaInts, 64);
			for (u32 i = 0; i < 64; ++i)
			{
				Assert::IsTrue(A[i] == oneInt);
				Assert::IsTrue(B[i] == alottaInts[i]);
			}

			DynamicArray<int> C(oneInt, 8, 8);
			DynamicArray<int> D(1, 8, 8);
			D.Store(alottaInts, 64);
			for (u32 i = 0; i < 8; ++i)
			{

				for (u32 j = 0; j < 8; ++j)
				{
					Assert::IsTrue(C(i, j) == oneInt);
					Assert::IsTrue(D(i, j) == alottaInts[8 * j + i]);
				}
			}

			DynamicArray<int> E(oneInt, 4, 4, 4);
			DynamicArray<int> F(1, 4, 4, 4);
			F.Store(alottaInts, 64);
			for (u32 i = 0; i < 4; ++i)
			{
				for (u32 j = 0; j < 4; ++j)
				{
					for (u32 k = 0; k < 4; ++k)
					{
						Assert::IsTrue(E(i, j, k) == oneInt);
						Assert::IsTrue(F(i, j, k) == alottaInts[16 * k + 4 * j + i]);
					}
				}
			}

			//copy ctor
			DynamicArray<int> copy1d(B);
			DynamicArray<int> copy2d(D);
			DynamicArray<int> copy3d(F);

			//fill in and equals
			copy1d.Clear(oneInt);
			Assert::IsTrue(A == copy1d);
			for (u32 i = 0; i < 64; ++i)
			{
				Assert::IsTrue(A[i] == copy1d[i]);
			}

			copy2d.Clear(oneInt);
			Assert::IsTrue(C == copy2d);
			for (u32 i = 0; i < 8; ++i)
			{
				for (u32 j = 0; j < 8; ++j)
				{
					Assert::IsTrue(C(i, j) == copy2d(i, j));
				}
			}

			copy3d.Clear(oneInt);
			Assert::IsTrue(E == copy3d);
			for (u32 i = 0; i < 4; ++i)
			{
				for (u32 j = 0; j < 4; ++j)
				{
					for (u32 k = 0; k < 4; ++k)
					{
						Assert::IsTrue(E(i, j, k) == copy3d(i, j, k));
					}
				}
			}


			//should be same as the beginning

			for (u32 i = 0; i < 64; ++i)
			{
				Assert::IsTrue(A[i] == oneInt);
				Assert::IsTrue(B[i] == alottaInts[i]);
			}

			for (u32 i = 0; i < 8; ++i)
			{

				for (u32 j = 0; j < 8; ++j)
				{
					Assert::IsTrue(C(i, j) == oneInt);
					Assert::IsTrue(D(i, j) == alottaInts[8 * j + i]);
				}
			}

			for (u32 i = 0; i < 4; ++i)
			{
				for (u32 j = 0; j < 4; ++j)
				{
					for (u32 k = 0; k < 4; ++k)
					{
						Assert::IsTrue(E(i, j, k) == oneInt);
						Assert::IsTrue(F(i, j, k) == alottaInts[16 * k + 4 * j + i]);
					}
				}
			}

			DynamicArray<int> copyAssign = B;

			Assert::IsTrue(B == copyAssign);
		}

		TEST_METHOD(StackTest)
		{
			Stack<int> stack;
			Assert::IsTrue(stack.IsEmpty());
			Assert::IsFalse(stack.IsFull());

			//push
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);
			stack.Push(4);
			stack.Push(5);

			//array push
			int aFewInts[4] = { 1045, 2332, 5401, 5 };
			stack.Push(aFewInts, 4);

			//shrink
			Assert::IsFalse(stack.IsEmpty());
			Assert::IsFalse(stack.IsFull());
			stack.Shrink();
			Assert::IsFalse(stack.IsEmpty());
			Assert::IsTrue(stack.IsFull());

			//queries
			stack.Push(6);
			Assert::IsTrue(stack.Capacity() == 18);
			Assert::IsTrue(stack.Size() == 10);

			//reserve
			stack.Reserve(30);
			Assert::IsTrue(stack.Capacity() == 30);
			Assert::IsTrue(stack.Size() == 10);

			Stack<int> copy(stack);
			Assert::IsTrue(copy.Capacity() == 30);
			Assert::IsTrue(copy.Size() == 10);

			stack.Clear();
			Assert::IsTrue(stack.Capacity() == 30);
			Assert::IsTrue(stack.Size() == 0);

			Assert::IsTrue(copy.Peek() == 6);
			Assert::IsTrue(copy.Pull() == 6);
			Assert::IsTrue(copy.Peek() == 5);
			Assert::IsTrue(copy.Pull() == 5);
			Assert::IsTrue(copy.Peek() == 5401);
			Assert::IsTrue(copy.Pull() == 5401);
			Assert::IsTrue(copy.Peek() == 2332);
			Assert::IsTrue(copy.Pull() == 2332);
			Assert::IsTrue(copy.Peek() == 1045);
			Assert::IsTrue(copy.Pull() == 1045);
			Assert::IsTrue(copy.Peek() == 5);
			Assert::IsTrue(copy.Pull() == 5);
			Assert::IsTrue(copy.Peek() == 4);
			Assert::IsTrue(copy.Pull() == 4);
			Assert::IsTrue(copy.Peek() == 3);
			Assert::IsTrue(copy.Pull() == 3);
			Assert::IsTrue(copy.Peek() == 2);
			Assert::IsTrue(copy.Pull() == 2);
			Assert::IsTrue(copy.Peek() == 1);
			Assert::IsTrue(copy.Pull() == 1);

			Assert::IsTrue(copy.IsEmpty());

			copy.Destroy();
			Assert::IsTrue(copy.Capacity() != 30);
			Assert::IsTrue(copy.Size() == 0);
			Assert::IsTrue(stack.Capacity() == 30);
			Assert::IsTrue(stack.Size() == 0);


		}


		TEST_METHOD(PoolTest)
		{
			using namespace Abstracts;
			Pool<u64> test(256);

			while (!test.IsFull())
			{
				test.Fill(1024);
			}

			//test.Fill();

			for (u32 i = 0; i < test.Size(); i += 2)
			{
				 u64 freed = *test.Get(i);
				 test.Free(i);
				 test.Fill(freed >> 1);
			}

			for (u32 i = 0; i < test.Size(); i += 3)
			{
				u64 freed = *test.Get(i);
				test.Free(i);
				test.Fill(freed >> 1);
			}

			for (u32 i = 0; i < test.Size(); i += 4)
			{
				u64 freed = *test.Get(i);
				test.Free(i);
				test.Fill(freed >> 1);
			}

			Assert::IsTrue(128 == *test.Get(0));
			Assert::IsTrue(1024 == *test.Get(1));
			Assert::IsTrue(512 == *test.Get(2));
			Assert::IsTrue(512 == *test.Get(3));
			Assert::IsTrue(256 == *test.Get(4));
			Assert::IsTrue(1024 == *test.Get(5));
			Assert::IsTrue(256 == *test.Get(6));
			Assert::IsTrue(1024 == *test.Get(7));
			Assert::IsTrue(256 == *test.Get(8));
			Assert::IsTrue(512 == *test.Get(9));
			Assert::IsTrue(512 == *test.Get(10));
			Assert::IsTrue(1024 == *test.Get(11));
			Assert::IsTrue(128 == *test.Get(12));
			Assert::IsTrue(1024 == *test.Get(13));
			Assert::IsTrue(512 == *test.Get(14));
			Assert::IsTrue(512 == *test.Get(15));

			//copying
			Pool<u64> copy(test);

			for (u32 i = 0; i < copy.Size(); i += 5)
			{
				u64 freed = *copy.Get(i);
				copy.Free(i);
				copy.Fill(freed >> 1);
			}

			Assert::IsTrue(64 == *copy.Get(0));
			Assert::IsTrue(1024 == *copy.Get(1));
			Assert::IsTrue(512 == *copy.Get(2));
			Assert::IsTrue(512 == *copy.Get(3));
			Assert::IsTrue(256 == *copy.Get(4));
			Assert::IsTrue(512 == *copy.Get(5));
			Assert::IsTrue(256 == *copy.Get(6));
			Assert::IsTrue(1024 == *copy.Get(7));
			Assert::IsTrue(256 == *copy.Get(8));
			Assert::IsTrue(512 == *copy.Get(9));
			Assert::IsTrue(256 == *copy.Get(10));
			Assert::IsTrue(1024 == *copy.Get(11));
			Assert::IsTrue(128 == *copy.Get(12));
			Assert::IsTrue(1024 == *copy.Get(13));
			Assert::IsTrue(512 == *copy.Get(14));
			Assert::IsTrue(256 == *copy.Get(15));


			Assert::IsTrue(128 == *test.Get(0));
			Assert::IsTrue(1024 == *test.Get(1));
			Assert::IsTrue(512 == *test.Get(2));
			Assert::IsTrue(512 == *test.Get(3));
			Assert::IsTrue(256 == *test.Get(4));
			Assert::IsTrue(1024 == *test.Get(5));
			Assert::IsTrue(256 == *test.Get(6));
			Assert::IsTrue(1024 == *test.Get(7));
			Assert::IsTrue(256 == *test.Get(8));
			Assert::IsTrue(512 == *test.Get(9));
			Assert::IsTrue(512 == *test.Get(10));
			Assert::IsTrue(1024 == *test.Get(11));
			Assert::IsTrue(128 == *test.Get(12));
			Assert::IsTrue(1024 == *test.Get(13));
			Assert::IsTrue(512 == *test.Get(14));
			Assert::IsTrue(512 == *test.Get(15));



			//resizing
			for (u32 i = 0; i < test.Size(); ++i)
			{
				test.Free(i);
			}

			Assert::IsTrue(test.IsEmpty());

			test.Shrink(0);
			test.Expand(30);

			Assert::IsTrue(test.IsEmpty());

			while (!test.IsFull())
			{
				test.Fill(-1);
			}
			Mathematics::Random::Initialize();
			for (u32 i = 0; i < test.Size(); ++i)
			{
				u32 rand = Mathematics::Random::Integer(0, 2);
				if (0 == rand)
				{
					test.Free(i);
				}
			}

			test.Shrink(10);

			while (!test.IsFull())
			{
				test.Fill(9999);
			}

			for (u32 i = 0; i < test.Size(); ++i)
			{
				std::cerr << *test.Get(i) << std::endl;
				test.Free(i);
			}

			Assert::IsTrue(test.IsEmpty());
		}
	};
}