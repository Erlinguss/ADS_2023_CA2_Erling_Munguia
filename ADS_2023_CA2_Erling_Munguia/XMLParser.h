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
    Tree<File>* root;


    bool validateXML(const string& xmlDocument);
    Tree<File*>* builtTree(const string& xmlDocument);
 

    int calculateMemoryUsageBFS(Tree<File>* folder) const;
     //================
    //void displayFolderContents(Tree<string>* currentNode);

};

