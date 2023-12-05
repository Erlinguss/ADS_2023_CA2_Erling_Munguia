#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_Erling_Munguia/TreeIterator.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TreeIteratorTest
{
	TEST_CLASS(TreeIteratorTest)
	{
	public:

			
			//===Helper function used to set up the tree used for testing.===
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
			
		};
}
