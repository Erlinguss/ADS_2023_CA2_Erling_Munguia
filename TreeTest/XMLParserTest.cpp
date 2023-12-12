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

        TEST_METHOD(TestBuildTree_EmptyDocument)
        {
            XMLParser xmlParser("");
            string emptyXML = "";
            Tree<File*>* tree = xmlParser.builtTree(emptyXML);

            Assert::IsNull(tree);
        }
        TEST_METHOD(TestBuildTree_NestedFoldersAndFiles)
        {
            XMLParser xmlParser("");
            string nestedXML = "<dir><name>Root</name>"
                "<file><name>git1.txt</name><length>10</length><type>txt</type></file>"
                "<dir><name>Subfolder1</name>"
                "<file><name>git2.txt</name><length>20</length><type>txt</type></file>"
                "<dir><name>Subfolder2</name>"
                "<file><name>git3.txt</name><length>30</length><type>txt</type></file>"
                "</dir>"
                "</dir>"
                "</dir>";
            Tree<File*>* tree = xmlParser.builtTree(nestedXML);
            Assert::IsNotNull(tree);
        }


        TEST_METHOD(TestMemoryUsageBFS)
        {
            XMLParser xmlParser("");
            string xmlDocument = "<dir><file><name>ADS_Single_LinkedList_Exercises</name><length>100</length><type>txt</type></file><dir><file><name>file2</name><length>500</length><type>txt</type></file></dir></dir>";
            Tree<File*>* tree = xmlParser.builtTree(xmlDocument);
            int memoryUsage = xmlParser.memoryUsageBFS(tree);

            Assert::AreEqual(600, memoryUsage);
        }


        TEST_METHOD(TestMemoryUsageBFS_EmptyTree)
        {
            XMLParser xmlParser("");
            Tree<File*>* tree = nullptr;
            int memoryUsage = xmlParser.memoryUsageBFS(tree);
            Assert::AreEqual(0, memoryUsage);
        }

        TEST_METHOD(TestPruneEmptyFolders_NoEmptyFolders)
        {
            XMLParser xmlParser("");
            string xmlDocument = "<dir><file><name>file1</name><length>100</length><type>txt</type></file></dir>";
            Tree<File*>* tree = xmlParser.builtTree(xmlDocument);

            Assert::IsNotNull(tree->children.getIterator().item());

            xmlParser.pruneEmptyFolders(tree);

            Assert::IsNotNull(tree->children.getIterator().item());
        }


        TEST_METHOD(TestFindItem)
        {
            XMLParser xmlParser("");
            Tree<File*>* tree = xmlParser.builtTree("<dir><name>ADS_Single_LinkedList_Exercises</name><file><name>.gitattributes</name><length>2581 b</length><type>gitattributes</type></file></dir>");
            Tree<File*>* foundNode = xmlParser.findItem("ADS_Single_LinkedList_Exercises", tree, "");
            Assert::IsNotNull(foundNode);
        }

        TEST_METHOD(TestFindItemNotFound)
        {
            XMLParser xmlParser("");
            Tree<File*>* tree = xmlParser.builtTree("<dir><name>ADS_Single_LinkedList_Exercises</name><file><name>.gitattributes</name><length>2581 b</length><type>gitattributes</type></file></dir>");
            Tree<File*>* foundNode = xmlParser.findItem("ADS_Single_LinkedList_Exercises1", tree, "");
            Assert::IsNull(foundNode);
        }

        TEST_METHOD(TestDisplayFolderContents)
        {
            XMLParser xmlParser("");
            string xmlDocument = "<dir><name>Root</name>"
                "<file><name>git1.txt</name><length>100</length><type>txt</type></file>"
                "<file><name>git2.txt</name><length>150</length><type>txt</type></file>"
                "<dir><name>Subfolder</name>"
                "<file><name>git3.txt</name><length>200</length><type>txt</type></file>"
                "<file><name>git4.txt</name><length>120</length><type>txt</type></file>"
                "</dir>"
                "</dir>";
            Tree<File*>* tree = xmlParser.builtTree(xmlDocument);

            xmlParser.displayFolderContents(tree);
        }

        TEST_METHOD(TestDisplayFolderContents_SingleFile)
        {
            XMLParser xmlParser("");
            string xmlDocument = "<file><name>git1.txt</name><length>100</length><type>txt</type></file>";
            Tree<File*>* tree = xmlParser.builtTree(xmlDocument);

            xmlParser.displayFolderContents(tree);
        }

        TEST_METHOD(TestDisplayFolderContents_EmptyFolder)
        {
            XMLParser xmlParser("");
            string xmlDocument = "<dir><name>EmptyFolder</name></dir>";
            Tree<File*>* tree = xmlParser.builtTree(xmlDocument);

            xmlParser.displayFolderContents(tree);
        }

        TEST_METHOD(TestDisplayFolderContents_NestedFolders)
        {
            XMLParser xmlParser("");
            string xmlDocument = "<dir><name>Root</name>"
                "<dir><name>Subfolder1</name><file><name>file1.txt</name><length>100</length><type>txt</type></file></dir>"
                "<dir><name>Subfolder2</name><file><name>file2.txt</name><length>150</length><type>txt</type></file></dir>"
                "</dir>";
            Tree<File*>* tree = xmlParser.builtTree(xmlDocument);

            xmlParser.displayFolderContents(tree);
        }



	};
}

