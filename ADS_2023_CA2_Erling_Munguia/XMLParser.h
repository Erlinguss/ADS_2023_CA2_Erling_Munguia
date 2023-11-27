#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include "Tree.h"
#include "structure.h"
using namespace std;

class XMLParser
{
public:
    XMLParser(const string& xmlFileName); 
    void parse(); 
private:
    std::string xmlFileName;
    //Tree<std::string>* root;
    Tree<File>* root;


    bool validateXML(const string& xmlDocument);
    void builtTree(const string& xmlDocument);


};

