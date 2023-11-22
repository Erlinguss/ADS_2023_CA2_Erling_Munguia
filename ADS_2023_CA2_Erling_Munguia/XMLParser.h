#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include "Tree.h"
using namespace std;

class XMLParser
{
public:
    XMLParser(const string& xmlFileName); 
    void parse(); 
private:
    std::string xmlFileName;
    Tree<std::string>* root;


    bool validateXML(const string& xmlDocument);
    void builtTree(const string& xmlDocument);


};

