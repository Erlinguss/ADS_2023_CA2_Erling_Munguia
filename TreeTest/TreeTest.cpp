#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_Erling_Munguia/Tree.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
	TEST_CLASS(TreeTest)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			Tree<int> tree(1);
			Assert::AreEqual(1, tree.data);
			Assert::IsNull(tree.parent);
			Assert::AreEqual(0, tree.children.size());
		}

		TEST_METHOD(TestCountOneItem)
		{
			Tree<int> tree(1);
			Assert::AreEqual(1, tree.count());
		}

		TEST_METHOD(TestCountOneItemWithChildrenAndSubChildren)
		{
			Tree<int> tree(1);
			Tree<int> childOne(2);
			Tree<int> childTwo(3);
			Tree<int> subChild(4);
			childTwo.children.append(&subChild);
			tree.children.append(&childOne);
			tree.children.append(&childTwo);
			Assert::AreEqual(2, childTwo.count());
			Assert::AreEqual(4, tree.count());
		}

		TEST_METHOD(TestEmptyTree)
		{
			Tree<int> emptyTree(0);
			Assert::AreEqual(1, emptyTree.count());
			Assert::IsNull(emptyTree.parent);
			Assert::AreEqual(0, emptyTree.children.size());
		}

		TEST_METHOD(TestMultipleLevels)
		{
			Tree<int> tree(1);
			Tree<int> childOne(2);
			Tree<int> childTwo(3);
			Tree<int> subChild(4);
			Tree<int> subSubChild(5);
			subChild.children.append(&subSubChild);
			childTwo.children.append(&subChild);
			tree.children.append(&childOne);
			tree.children.append(&childTwo);
			Assert::AreEqual(5, tree.count());
		}

		TEST_METHOD(TestDataRetrieval)
		{
			Tree<std::string> stringTree("Root");
			Assert::AreEqual(std::string("Root"), stringTree.getData());
		}

		TEST_METHOD(TestGetRootSingleItem)
		{
			Tree<int> singleItem(1);
			Tree<int>* singleItemRoot = singleItem.getRoot();

			Assert::IsNotNull(singleItemRoot);
			Assert::AreEqual(1, singleItemRoot->data);
		}

		TEST_METHOD(TestGetParentNull)
		{
			Tree<int> singleItem(1);

			Tree<int>* singleItemParent = singleItem.parent;

			Assert::IsNull(singleItemParent);
		}

		TEST_METHOD(TestGetDataWithNonIntegerType)
		{
			Tree<std::string> root("Root");

			Assert::AreEqual(std::string("Root"), root.getData());
		}

	};
}
