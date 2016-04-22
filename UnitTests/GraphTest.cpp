#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Abstracts;

namespace AbstractsTest
{		
	TEST_CLASS(GraphTest)
	{
	public:		

		TEST_METHOD(GraphConstruction)
		{
			Graph tester;
			tester.Allocate(153);
			Graph::Node& heldNode = tester.GetNode(42);
			Assert::IsTrue(tester.GetNumberOfNodes() == 153);
			tester.Free();
			Assert::IsTrue(tester.GetNumberOfNodes() == 0);
		}

		TEST_METHOD(NodeHandling)
		{
			Graph tester;
			tester.Allocate(3);
			Graph::Node& validNode = tester.GetNode(2);
			Assert::IsTrue(
				validNode.GetNumberOfNeighbours() == 0);
			Graph::Node& otherNode = tester.GetNode(1);
			validNode.MakeAdjacentTo(&otherNode);
			otherNode.MakeAdjacentTo(&validNode);
			Assert::IsTrue(
				validNode.GetNumberOfNeighbours() == 1);
			Assert::IsTrue(
				otherNode.GetNumberOfNeighbours() == 1);
			tester.Free();
		}
		
		TEST_METHOD(GridConstruction)
		{
			Grid testGrid;
			testGrid.Initialize(3, 3);
			Assert::AreEqual(testGrid.GetGraph().GetNumberOfNodes(), u32(3 * 3));
			testGrid.Free();
			Assert::AreEqual(testGrid.GetGraph().GetNumberOfNodes(), u32(0));
		}
	};
}