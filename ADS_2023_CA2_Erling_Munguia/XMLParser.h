#pragma once
#include <string>
using namespace std;

class XMLParser
{
public:
    XMLParser(const string& xmlFileName); 
    void parse(); 
private:
    string xmlFileName;
};



XMLParser::XMLParser(const string& xmlFileName)
{

}
void XMLParser::parse()
{

}


