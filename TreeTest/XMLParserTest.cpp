#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_Erling_Munguia/XMLParser.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace XMLParserTest
{
	TEST_CLASS(XMLParserTest)
	{
	public:
        TEST_METHOD(TestValidateXML_ValidDocument)
        {
            XMLParser xmlParser("");
            string validXML = "<dir><name>ADS_Single_LinkedList_Exercises</name><file><name>.gitattributes</name><length>2581 b</length><type>gitattributes</type></file></dir>";
            Assert::IsTrue(xmlParser.validateXML(validXML));
        }

        TEST_METHOD(TestValidateXML_InvalidDocument)
        {
            XMLParser xmlParser("");
            string invalidXML = "<dir><name>ADS_Single_LinkedList_Exercises</name><file><name>.gitattributes</name><length>2581 b</length><type>gitattributes</type></dir>";
            Assert::IsFalse(xmlParser.validateXML(invalidXML));
        }

        TEST_METHOD(TestBuildTree_ValidDocument)
        {
            XMLParser xmlParser("");
            string validXML = "<dir><name>ADS_Single_LinkedList_Exercises</name><file><name>.gitattributes</name><length>2581 b</length><type>gitattributes</type></file></dir>";
            Tree<File*>* tree = xmlParser.builtTree(validXML);
            Assert::IsNotNull(tree);
        }

        TEST_METHOD(TestBuildTree_InvalidDocument)
        {
            XMLParser xmlParser("");
            string invalidXML = "<dir><name>ADS_Single_LinkedList_Exercises</name><file><name>.gitattributes</name><length>2581 b</length><type>gitattributes</type></file></dir>";
            Tree<File*>* tree = xmlParser.builtTree(invalidXML);
            Assert::IsNull(tree);
        }


        TEST_METHOD(TestMemoryUsageBFS)
        {
            XMLParser xmlParser("");
            Tree<File*>* tree = xmlParser.builtTree("<dir><name>ADS_Single_LinkedList_Exercises</name><file><name>.gitattributes</name><length>2581 b</length><type>gitattributes</type></file></dir>");
            int memoryUsage = xmlParser.memoryUsageBFS(tree);
            Assert::AreEqual(2581, memoryUsage);
        }

        TEST_METHOD(TestPruneEmptyFolders)
        {
            XMLParser xmlParser("");
            Tree<File*>* tree = xmlParser.builtTree("<dir><dir><file><name>file1</name><length>100</length><type>txt</type></file></dir></dir>");
            xmlParser.pruneEmptyFolders(tree);
            Assert::IsNull(tree->children.getIterator().item());
        }




	};
}

