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

    
    Tree<File*>* getRoot() const {
        return root;
    }
    
    void setRoot(Tree<File*>* newRoot);
    int calculateMemoryUsageBFS(Tree<File>* folder) const;
    

private:
   
    std::string xmlFileName;
    Tree<File*>* root;
    bool validateXML(const string& xmlDocument);
    Tree<File*>* builtTree(const string& xmlDocument);
};

