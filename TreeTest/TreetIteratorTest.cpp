#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_Erling_Munguia/TreeIterator.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TreeIteratorTest
{
	TEST_CLASS(TreeIteratorTest)
	{
	public:

			
			//	=== Helper function used to set up the tree used for testing. ===
			void populateTree(Tree<int>*& root, Tree<int>*& cc2)
			{
				root = new Tree<int>(1);
				Tree<int>* c1 = new Tree<int>(2);
				Tree<int>* c2 = new Tree<int>(3);
				c1->parent = root;
				c2->parent = root;


				Tree<int>* cc1 = new Tree<int>(4);
				Tree<int>* cc3 = new Tree<int>(6);
				cc2 = new Tree<int>(5);
				cc1->parent = c1;
				cc2->parent = c1;
				cc3->parent = c1;
				root->children.append(c1);
				root->children.append(c2);
				c1->children.append(cc1);
				c1->children.append(cc2);
				c1->children.append(cc3);
			}
		
		    // ===Test the resetIterator function sets list and currentNode to nullptr if no tree is passed in. ===
			
			TEST_METHOD(TestResetIteratorNullPtr)
			{
				TreeIterator<int> iter(nullptr);
				Assert::IsNull(iter.childIter.list);
				Assert::IsNull(iter.childIter.currentNode);

			}

		
	        // ==Tests the resetIterator sets list and currentNode to nullptr if a tree with no children is passed in. ===

			TEST_METHOD(TestResetIteratorValidTreeNoChild)
			{
				Tree<int> t(1);
				TreeIterator<int> iter(&t);
				Assert::IsNotNull(iter.childIter.list);
				Assert::IsNull(iter.childIter.currentNode);

			}

			//===Tests the reset iterator function sets the childIter to the first child when a valid tree is passed in. ===
	
			TEST_METHOD(TestResetIteratorValidTreeWithChild)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				TreeIterator<int> iter(root);
				Assert::IsNotNull(iter.childIter.list);
				Assert::IsNotNull(iter.childIter.currentNode);
				Assert::AreEqual(2, iter.childIter.currentNode->data->data);

			}

			// ===Tests the root function moves the iterator to the root of the tree if it is set to a leaf node, cc2. ===
			TEST_METHOD(TestRoot)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(cc2);
				Assert::AreEqual(5, iter.node->data);
				iter.root();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(1, iter.node->data);
			}

			// === "Tests up method moves from leaf to parent (iterator at 5, parent 2), resetIterator to correct child node. ===
			TEST_METHOD(TestUp)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(cc2);
				Assert::AreEqual(5, iter.node->data);
				Assert::IsFalse(iter.childIter.isValid());

				iter.up();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(2, iter.node->data);
				Assert::AreEqual(4, iter.childIter.item()->getData());

				iter.up();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(1, iter.node->data);
				Assert::AreEqual(2, iter.childIter.item()->getData());


			}


			//===Tests UP function prevents iterator from going beyond the root and triggers reset on exceeding root.===
			TEST_METHOD(TestUpFromRoot)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				iter.childIter.advance();
				Assert::AreEqual(3, iter.childIter.item()->getData());
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(1, iter.node->data);
				iter.up();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(1, iter.node->data);
				Assert::AreEqual(2, iter.childIter.item()->getData());
			}


			// === Tests down function moves from root to correct child and works for any child node set by the child iterator. ===
			TEST_METHOD(TestDownFromRoot)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				Assert::AreEqual(1, iter.node->data);
				Assert::IsTrue(iter.childIter.isValid());
				Assert::AreEqual(2, iter.childIter.item()->getData());

				iter.down();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(2, iter.node->data);
				Assert::AreEqual(4, iter.childIter.item()->getData());
				iter.childForth();
				iter.down();
				Assert::IsNotNull(iter.node);
				Assert::AreEqual(5, iter.node->data);
				Assert::IsFalse(iter.childIter.isValid());

			}

			// ===Tests down function prevents iterator invalidation when there are no node children ===
			TEST_METHOD(TestDownFromLeaf)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(cc2);
				Assert::AreEqual(5, iter.node->data);
				Assert::IsFalse(iter.childIter.isValid());

				iter.down();
				Assert::AreEqual(5, iter.node->data);
				Assert::IsFalse(iter.childIter.isValid());

			}

			// === Tests child back method for iteratively moving back to the previous child node. ===
			TEST_METHOD(TestChildBack)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				Assert::AreEqual(2, iter.childIter.item()->getData());
				iter.childIter.advance();
				Assert::AreEqual(3, iter.childIter.item()->getData());
				iter.childBack();
				Assert::AreEqual(2, iter.childIter.item()->getData());

			}

			// === Tests the childForth method moves to teh next child element. ===
			TEST_METHOD(TestChildForth)
			{
				Tree<int>* root = nullptr;
				Tree<int>* cc2 = nullptr;
				populateTree(root, cc2);
				Assert::IsNotNull(root);
				TreeIterator<int> iter(root);
				Assert::AreEqual(2, iter.childIter.item()->getData());
				iter.childForth();
				Assert::AreEqual(3, iter.childIter.item()->getData());

			}

		





			
		};
}
