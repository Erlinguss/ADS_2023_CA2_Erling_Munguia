#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_Erling_Munguia/TreeIterator.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TreeIteratorTest
{
	TEST_CLASS(TreeIteratorTest)
	{
	public:

			void populateTree(Tree<int>*& root, Tree<int>*& cc2)
			{
				root = new Tree<int>(10);
				Tree<int>* c1 = new Tree<int>(20);
				Tree<int>* c2 = new Tree<int>(30);
				c1->parent = root;
				c2->parent = root;

				Tree<int>* cc1 = new Tree<int>(40);
				Tree<int>* cc3 = new Tree<int>(60);
				cc2 = new Tree<int>(50);
				cc1->parent = c1;
				cc2->parent = c1;
				cc3->parent = c1;
				root->children.append(c1);
				root->children.append(c2);
				c1->children.append(cc1);
				c1->children.append(cc2);
				c1->children.append(cc3);
			}

			TEST_METHOD(TestResetIteratorNullPtr)
			{
				TreeIterator<int> iter(nullptr);
				Assert::IsNull(iter.childIter.list);
				Assert::IsNull(iter.childIter.currentNode);
			}

			TEST_METHOD(TestRemoveChildEmptyList)
			{

				Tree<int> t(1);
				TreeIterator<int> iter(&t);

				iter.removeChild();

			}

			TEST_METHOD(TestChildValidAfterInsertions)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);

				TreeIterator<int> iter(root);

				iter.down();
				Assert::IsTrue(iter.childValid());

				iter.insertChildBefore(99);
				Assert::IsTrue(iter.childValid());

				iter.insertChildAfter(100);
				Assert::IsTrue(iter.childValid());
			}


			TEST_METHOD(TestResetIteratorValidTreeNoChild)
			{
				Tree<int> t(100);
				TreeIterator<int> iter(&t);
				Assert::IsNotNull(iter.childIter.list);
				Assert::IsNull(iter.childIter.currentNode);
			}

			TEST_METHOD(TestResetIteratorValidTreeWithChild)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				TreeIterator<int> iter(root);
				Assert::IsNotNull(iter.childIter.list);
				Assert::IsNotNull(iter.childIter.currentNode);
				Assert::AreEqual(20, iter.childIter.currentNode->data->data);
			}

			TEST_METHOD(TestRoot)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(cc2);
				Assert::AreEqual(50, iter.node->data);
				iter.root();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(10, iter.node->data);
			}

			TEST_METHOD(TestUp)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(cc2);
				Assert::AreEqual(50, iter.node->data);
				Assert::IsFalse(iter.childIter.isValid());

				iter.up();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(20, iter.node->data);
				Assert::AreEqual(40, iter.childIter.item()->getData());

				iter.up();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(10, iter.node->data);
				Assert::AreEqual(20, iter.childIter.item()->getData());
			}


			TEST_METHOD(TestUpFromRoot)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.childIter.advance();
				Assert::AreEqual(30, iter.childIter.item()->getData());
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(10, iter.node->data);
				iter.up();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(10, iter.node->data);
				Assert::AreEqual(20, iter.childIter.item()->getData());
			}


			TEST_METHOD(TestDownFromRoot)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				Assert::AreEqual(10, iter.node->data);
				Assert::IsTrue(iter.childIter.isValid());
				Assert::AreEqual(20, iter.childIter.item()->getData());

				iter.down();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(20, iter.node->data);
				Assert::AreEqual(40, iter.childIter.item()->getData());
				iter.childForth();
				iter.down();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(50, iter.node->data);
				Assert::IsFalse(iter.childIter.isValid());
			}

			TEST_METHOD(TestDownFromLeaf)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(cc2);
				Assert::AreEqual(50, iter.node->data);
				Assert::IsFalse(iter.childIter.isValid());

				iter.down();
				Assert::AreEqual(50, iter.node->data);
				Assert::IsFalse(iter.childIter.isValid());
			}


			TEST_METHOD(TestChildBack)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				Assert::AreEqual(20, iter.childIter.item()->getData());
				iter.childIter.advance();
				Assert::AreEqual(30, iter.childIter.item()->getData());
				iter.childBack();
				Assert::AreEqual(20, iter.childIter.item()->getData());
			}


			TEST_METHOD(TestChildForth)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				Assert::AreEqual(20, iter.childIter.item()->getData());
				iter.childForth();
				Assert::AreEqual(30, iter.childIter.item()->getData());
			}


			TEST_METHOD(TestChildStart)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.down();
				Assert::AreEqual(40, iter.childIter.item()->getData());
				iter.childIter.advance();
				iter.childIter.advance();
				Assert::AreEqual(60, iter.childIter.item()->getData());
				iter.childStart();
				Assert::AreEqual(40, iter.childIter.item()->getData());
			}


			TEST_METHOD(TestChildEnd)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.down();
				Assert::AreEqual(40, iter.childIter.item()->getData());
				iter.childEnd();
				Assert::AreEqual(60, iter.childIter.item()->getData());
			}


			TEST_METHOD(TestAppendChild)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.down();
				Assert::AreEqual(40, iter.childIter.item()->getData());
				iter.appendChild(70);
				iter.childEnd();
				Assert::AreEqual(70, iter.childIter.item()->getData());
			}

			TEST_METHOD(TestPrependChild)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.down();
				Assert::AreEqual(40, iter.childIter.item()->getData());
				iter.prependChild(70);
				Assert::AreEqual(70, iter.childIter.item()->getData());
			}


			TEST_METHOD(TestInsertChildBefore)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.down();
				int startChildren[] = { 40,50,60 };
				for (int i = 0; i < 3; i++)
				{
					Assert::AreEqual(startChildren[i], iter.childIter.item()->getData());
					if (i != 2)
					{
						iter.childForth();
					}
				}
				iter.childStart();
				Assert::IsTrue(iter.childIter.isValid());
				iter.childForth();
				Assert::AreEqual(50, iter.childIter.item()->getData());
				iter.insertChildBefore(70);
				iter.childStart();
				int endChildren[] = { 40,70,50,60 };
				for (int i = 0; i < 4; i++)
				{
					Assert::AreEqual(endChildren[i], iter.childIter.item()->getData());
					iter.childForth();
				}
				iter.childStart();
			}


			TEST_METHOD(TestInsertChildAfter)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.down();
				int startChildren[] = { 40,50,60 };
				for (int i = 0; i < 3; i++)
				{
					Assert::AreEqual(startChildren[i], iter.childIter.item()->getData());
					if (i != 2)
					{
						iter.childForth();
					}
				}
				iter.childStart();
				Assert::AreEqual(40, iter.childIter.item()->getData());
				iter.insertChildAfter(70);
				Assert::AreEqual(40, iter.childIter.item()->getData());
				iter.childStart();
				int endChildren[] = { 40,70,50,60 };
				for (int i = 0; i < 4; i++)
				{
					Assert::AreEqual(endChildren[i], iter.childIter.item()->getData());
					iter.childForth();
				}
				iter.childStart();
			}

			TEST_METHOD(TestRemoveChild)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.down();
				int startChildren[] = { 40,50,60 };
				for (int i = 0; i < 3; i++)
				{
					Assert::AreEqual(startChildren[i], iter.childIter.item()->getData());
					if (i != 2)
					{
						iter.childForth();
					}
				}
				iter.childStart();
				iter.childForth();
				iter.removeChild();
				iter.childStart();
				int endChildren[] = { 40,60 };
				for (int i = 0; i < 2; i++)
				{
					Assert::AreEqual(endChildren[i], iter.childIter.item()->getData());
					iter.childForth();
				}
				iter.childStart();
			}

		};
}
