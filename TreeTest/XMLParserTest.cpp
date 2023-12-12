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
	};
}

