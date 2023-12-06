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
    int memoryUsageBFS(Tree<File*>* folder) const;
    void pruneEmptyFolders(Tree<File*>* node);
    Tree<File*>* findItem(const string& itemName, Tree<File*>* currentNode, string currentPath = "");
    void displayFolderContents(Tree<File*>* folder) const;
    bool containsNonEmptyFiles(Tree<File*>* folder);

private:

    std::string xmlFileName;
    Tree<File*>* root;
    bool validateXML(const string& xmlDocument);
    Tree<File*>* builtTree(const string& xmlDocument);
};

