
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include "DList.h"
#include "Tree.h"
#include "structure.h"
#include "TreeIterator.h"
#include "XMLParser.h"
using namespace std;

#include <SFML/Graphics.hpp>
#include "SFML/Graphics.hpp"


// ========= Implementation of XMLParser Validation ============
bool XMLParser::validateXML(const string& xmlDocument) {
    stack<string> tagStack;
    bool hasRoot = false;
    
    for (size_t i = 0; i < xmlDocument.size(); ++i) {
       
        if (xmlDocument[i] == '<') {
            size_t start = i + 1;
            size_t end = xmlDocument.find('>', start);
         
            if (end == string::npos) {
                return false;
            }

            string tag = xmlDocument.substr(start, end - start);
            if (tag.empty()) {
                return false;
            }

            if (tag[0] == '/') {
                if (tagStack.empty() || tag.substr(1) != tagStack.top()) {
               
                    return false;
                }
                tagStack.pop();
            }
            else {
                if (!hasRoot) {
                    hasRoot = true;
                }
                tagStack.push(tag);
            }
            i = end;
        }
    }
    return tagStack.empty();

}

// =========== Display the Tree ==============
template <class T>
void displayTree(TreeIterator<T> iter, string indent)
{
    cout << indent << iter.node->data;
    if (iter.childValid())
    {
        cout << "(" << endl;

        while (iter.childValid())
        {
            TreeIterator<T> iter2(iter.childIter.currentNode->data);
            displayTree(iter2, "\t" + indent);
            iter.childForth();
        }
        cout << indent << ")";
    }
    cout << endl;
}

// =========== Build the Tree ==============
Tree<File*>* XMLParser::builtTree(const string& xmlDocument) {
    stack<Tree<File>*> nodeStack;
    size_t i = 0;
    File *currentFile = nullptr;
    Tree<File*>* tree =nullptr;
    TreeIterator<File*> *iter = nullptr;

    try {
        Tree<File>* newNode = nullptr;

        while (i < xmlDocument.size()) {
          
            if (xmlDocument[i] == '<') {
                
                size_t start = i + 1;
                size_t end = xmlDocument.find('>', start);
                if (end == string::npos) {
                    return tree;
                }

                string tag = xmlDocument.substr(start, end - start);
                if (tag.empty()) {
                    return tree;
                }

                if (tag[0] != '/') 
                {
                    size_t dataStart = end + 1;
                    size_t dataEnd = xmlDocument.find('<', dataStart);
                    string data = xmlDocument.substr(dataStart, dataEnd - dataStart);
                  
                    if (tag == "file")
                    {
                        currentFile = new File();
                        iter->appendChild(currentFile);
                    }
                    else if (tag == "dir") 
                    {
                        currentFile = new File();
                                    
                            if (iter == nullptr)
                            {
                                tree = new Tree<File*>(currentFile);
                                iter = new TreeIterator<File*>(tree);
                            }
                            else
                            {
                                iter->appendChild(currentFile);
                                iter->childEnd();
                                iter->down();
                            }
                    
                   }
                       
                else if (tag == "name") {
                    currentFile->name = data;
                }
                else if (tag == "length") {
                    currentFile->size = stoi(data);
                }
                else if (tag == "type") {
                    currentFile->type = data;
                 
                }
                    i = dataEnd;    
                }
                else if(tag[0] == '/' && tag=="/dir") {
                    iter->up();
                    i = end + 1;
                }
                else
                {
                    i = end + 1;
                } 
              
            }
            else {
                ++i;
            }
        }
        return tree;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}


XMLParser::XMLParser(const string& xmlFileName) : xmlFileName(xmlFileName),
root(nullptr) {}


// ===== Function to parse the Tree =====
void XMLParser::parse() {
    ifstream file(xmlFileName);
    string xmlDocument = "";
    string line;
    while (getline(file, line))
    {
        xmlDocument += line;
    }

    if (!validateXML(xmlDocument)) {
        cout << "Invalid XML document." << endl;
        return;
    }

    Tree<File*>* tree = builtTree(xmlDocument);

    if (tree != nullptr) {
        //setRoot(tree);
        cout << "\nTree structure:" << endl;
        displayTree(TreeIterator<File*>(tree), ""); 
    }
}


int XMLParser::calculateMemoryUsageBFS(Tree<File>* folder) const {
    if (folder == nullptr) {
        return 0;
    }

    int totalMemory = 0;
    queue<Tree<File>*> q;
    q.push(folder);

    while (!q.empty()) {
        Tree<File>* current = q.front();
        q.pop();

        totalMemory += current->getData().size;

        DListIterator<Tree<File>*> childIter = current->children.getIterator();
        while (childIter.isValid()) {
            q.push(childIter.item());
            childIter.advance();
        }
    }

    return totalMemory;
}



int main() {
    int choice;
    string xmlFileName;
    XMLParser xmlParser("");  

    do {
        cout << "===================================================== \n";
        cout << "|                Select an option:                  |\n";
        cout << "===================================================== \n";
        cout << "| 1. Validate XML, built the tree and Displayed     |\n";
        cout << "| 2. Number of items within a given folder directory|\n";
        cout << "| 3. Memory used by a given folder.                 |\n";
        cout << "| 4. Prune the tree to remove empty folders         |\n";
        cout << "| 5. Find a given file/folder                       |\n";
        cout << "| 6. Display the contents of a given folder         |\n";
        cout << "| 0. Exit.                                          |\n";
        cout << "===================================================== \n";
        cout << "| Enter your choice:                                |\n";
        cout << "===================================================== \n";

        cin >> choice;

        switch (choice) {
        case 1:
        
            xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia/ADS_2023_CA2_Erling_Munguia/Example1.xml";
            xmlParser = XMLParser(xmlFileName); 
            xmlParser.parse();
            break;
        
        case 2:

            //cout << "Number of items: " << xmlParser.getRoot()->count() << endl;
            break;
        
        case 3:
            if (xmlParser.getRoot() != nullptr) {
               // cout << "Memory used by the folder: " << xmlParser.calculateMemoryUsageBFS() << " bytes\n";
            }
            else {
                cout << "Root folder not found.\n";
            }
            break;


        case 4: 
            
            break;
        
        case 5:

            break;
        case 6:

            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}




