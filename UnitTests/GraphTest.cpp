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
			Graph::Node& invalidNode = tester.GetNode(42);
			Graph::Node& validNode = tester.GetNode(2);
			Assert::IsTrue(
				validNode.GetNumberOfNeighbours() == 0);
			Graph::Node& otherNode = tester.GetNode(1);
			validNode.AddNeighbour(&otherNode);
			otherNode.AddNeighbour(&validNode);
			Assert::IsTrue(
				validNode.GetNumberOfNeighbours() == 1);
			Assert::IsTrue(
				otherNode.GetNumberOfNeighbours() == 1);
		}
		
		TEST_METHOD(GridConstruction)
		{
			Grid testGrid;
			testGrid.Initialize(203, 5);
		}
	};
}