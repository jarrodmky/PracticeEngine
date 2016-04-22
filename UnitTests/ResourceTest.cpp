#include "stdafx.h"
#include "CppUnitTest.h"
#include "Resource.h"
#include "Library.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Serialization;

namespace CoreTest
{
	TEST_CLASS(ResourceTest)
	{
	public:
		
		class EmptyStandalone
		{

		};

		class OneByte
		{
			char member;
		};

		class TwelveBytes
		{
			char members[12];
		};

		TEST_METHOD(BlockAllocation)
		{
			//Assert::IsTrue(sizeof(EmptyStandalone) == 1);
			//Assert::IsTrue(sizeof(OneByte) == 1);
			//Assert::IsTrue(sizeof(TwelveBytes) == 12);

			//MemoryPool<1> BytePool(40);
			//MemoryPool<1000> KilobytePool(10);

			//MemoryHandle firstTicket = BytePool.Allocate(33);
			//MemoryHandle secondTicket = BytePool.Allocate(66);
			//MemoryHandle thirdTicket = BytePool.Allocate(99);

			//Assert::IsTrue(*(BytePool.Get<>(firstTicket)) == 33);
			//Assert::IsTrue(BytePool.IsValid(firstTicket));
			//Assert::IsTrue(*(BytePool.Get(secondTicket)) == 66);
			//Assert::IsTrue(BytePool.IsValid(secondTicket));
			//Assert::IsTrue(*(BytePool.Get(thirdTicket)) == 99);
			//Assert::IsTrue(BytePool.IsValid(thirdTicket));

			//MemoryHandle copyOfSecond(secondTicket);
			//Assert::IsTrue(*(BytePool.Get(copyOfSecond)) == 66);

			//BytePool.Free(secondTicket);




		}

		class SomeResource : public Resource<SomeResource>
		{
			
			virtual bool OnAquire(const std::string& p_Name)
			{
				std::cerr << "Aquired the resource: " << p_Name << std::endl;
				return true;
			}

			virtual void OnRelease()
			{
				std::cerr << "Released the resource!" << std::endl;
			}
		};

		typedef Library<SomeResource> SomeManager;

		class SomeOtherResource : public Resource<SomeOtherResource>
		{
			virtual bool OnAquire(const std::string& p_Name)
			{
				std::cerr << "Aquired the other resource: " << p_Name << std::endl;
				return true;
			}

			virtual void OnRelease()
			{
				std::cerr << "Released the other resource!" << std::endl;
			}
		};

		typedef Library<SomeOtherResource> SomeOtherManager;

		TEST_METHOD(ResourceAquisition)
		{
			SomeManager testManager("");
			SomeOtherManager otherTestManager("");

			SomeResource* resource(nullptr);
			resource = testManager.Borrow("a");
			
			SomeOtherResource* otherResource(nullptr);
			otherResource = otherTestManager.Borrow("a");
			otherResource = otherTestManager.Borrow("b");
			otherResource = otherTestManager.Borrow("a");

			Assert::IsTrue(otherResource->GetReferenceCount() == 3);

			testManager.Return(resource);
			
			resource = nullptr;
			resource = testManager.Borrow("b");
			resource = testManager.Borrow("b");
			resource = testManager.Borrow("b");
			resource = testManager.Borrow("b");
			resource = testManager.Borrow("b");
			resource = testManager.Borrow("b");
			resource = testManager.Borrow("b");

			Assert::IsTrue(resource->GetReferenceCount() == 8);
		}
	};
}