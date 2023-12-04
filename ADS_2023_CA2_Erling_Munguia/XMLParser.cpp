
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


//======= Implementation of XMLParser Validation ========
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
                //if (tagStack.empty() || tag.substr(1) != tagStack.top()) {
                if (tagStack.empty() || tag.compare(1, string::npos, tagStack.top()) != 0) {
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


// ========= Method Display the Tree =============
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


// ================ Build the Tree ===============
Tree<File*>* XMLParser::builtTree(const string& xmlDocument) {
    size_t i = 0;
    File* currentFile = nullptr;
    Tree<File*>* tree = nullptr;
    TreeIterator<File*>* iter = nullptr;

    try {
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

                if (tag[0] != '/') {
                    size_t dataStart = end + 1;
                    size_t dataEnd = xmlDocument.find('<', dataStart);
                    string data = xmlDocument.substr(dataStart, dataEnd - dataStart);

                    if (tag == "file") {
                        currentFile = new File();
                        if (iter != nullptr) {
                            iter->appendChild(currentFile);
                        }
                    }
                    else if (tag == "dir") {
                        currentFile = new File();
                        if (iter == nullptr) {
                            tree = new Tree<File*>(currentFile);
                            iter = new TreeIterator<File*>(tree);
                        }
                        else {
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
                else if (tag[0] == '/' && tag == "/dir") {
                    iter->up();
                    i = end + 1;
                }
                else {
                    i = end + 1;
                }
            }
            else {
                ++i;
            }
        }
        delete iter;  // === Release memory for the TreeIterator ===
        return tree;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return nullptr;
    }
}

// ========== Method set the Root ===============
void XMLParser::setRoot(Tree<File*>* newRoot) {
    root = newRoot;
}

XMLParser::XMLParser(const string& xmlFileName) : xmlFileName(xmlFileName),
root(nullptr) {}


// ========= Function to parse the Tree =========
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
        setRoot(tree);
        cout << "\nTree structure:" << endl;
        displayTree(TreeIterator<File*>(tree), ""); 
    }

}

//=== Task 2b. Function to calculate the memory usage BFS ===
int XMLParser::memoryUsageBFS(Tree<File*>* folder) const {
    if (folder == nullptr) {
        return 0;
    }

    int totalMemory = 0;
    queue<Tree<File*> *> q;
    q.push(folder);

    while (!q.empty()) {
        Tree<File*> * current = q.front();
        q.pop();

         totalMemory += current->getData()->size;
        
        DListIterator<Tree<File*>*> childIter = current->children.getIterator();
        while (childIter.isValid()) {
            q.push(childIter.item());
            childIter.advance();
        }    
    }
    return totalMemory;
}


// =====Task 2c: Function Prune the tree to remove empty folders =====
void XMLParser::pruneEmptyFolders(Tree<File*>* node) {
    DListIterator<Tree<File*>*> childIter = node->children.getIterator();
    while (childIter.isValid()) {
        Tree<File*>* childNode = childIter.item();
        pruneEmptyFolders(childNode);

        if (childNode->children.size() == 0) {
            // === Remove the empty folder ===
            node->children.remove(childIter);
            delete childNode;
            childIter = node->children.getIterator(); 
        }
        else {
            childIter.advance();
        }
    }
}


// ===== Task 2d: Find a given folder using Depth First Search ======
Tree<File*>* XMLParser::findItem(const string& partialName, Tree<File*>* currentNode, string currentPath) {
    string currentName = currentNode->getData()->name;
    string newPath = currentPath + "/" + currentName;

    if (currentName.find(partialName) != string::npos) {
        cout << "Path: " << newPath << endl;
        return currentNode;
    }

    DListIterator<Tree<File*>*> childIter = currentNode->children.getIterator();
    while (childIter.isValid()) {
        Tree<File*>* foundNode = findItem(partialName, childIter.item(), newPath);
        if (foundNode != nullptr) {
            return foundNode;
        }
        childIter.advance();
    }

    return nullptr;
}


// ==== Task 2e: Display the contents of a given folder including file sizes ====
void XMLParser::displayFolderContents(Tree<File*>* folder) const {
    if (folder == nullptr) {
        cout << "Invalid folder." << endl;
        return;
    }

    cout << "Contents of folder '" << folder->getData()->name << "':" << endl;

    DListIterator<Tree<File*>*> childIter = folder->children.getIterator();
    while (childIter.isValid()) {
        Tree<File*>* childNode = childIter.item();
        File* childData = childNode->getData();

        if (childData->type == "file") {
            cout << "File: " << childData->name << " (Size: " << childData->size << " bytes)" << endl;
        }

        // ==== Recursive call for subfolders ====
        if (childData->type == "dir") {
            displayFolderContents(childNode);
        }

        childIter.advance();
    }
}



int main() {
    int choice;
    string xmlFileName;
    XMLParser xmlParser("");  

    do {
        cout << "\n";
        cout << "=====================================================\n";
        cout << "|                     Menu System:                  |\n";
        cout << "=====================================================\n";
        cout << "| 1. Validate XML file, built and Display the tree  |\n";
        cout << "| 2. Number of items within a given folder directory|\n";
        cout << "| 3. Memory used by a given folder.                 |\n";
        cout << "| 4. Prune the tree to remove empty folders         |\n";
        cout << "| 5. Find a given file/folder                       |\n";
        cout << "| 6. Display the contents of a given folder         |\n";
        cout << "| 7. Exit.                                          |\n";
        cout << "=====================================================\n";
        cout << "| Enter your choice:                                |\n";
        cout << "=====================================================\n";

        cin >> choice;

        switch (choice) {
        case 1:
        
            xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia/ADS_2023_CA2_Erling_Munguia/Example1.xml";
            xmlParser = XMLParser(xmlFileName); 
            xmlParser.parse();
            break;
        
        case 2:
            if (xmlParser.getRoot() != nullptr) {
                cout << "Number of items (File/Folder): " << xmlParser.getRoot()->count() << endl;
            }
            else {
                cout << "Root folder not found.\n";
            }

            break;
        
        case 3:
             if (xmlParser.getRoot() != nullptr) {
               cout << "Memory used by the folder: " << xmlParser.memoryUsageBFS(xmlParser.getRoot()) << " bytes\n";
            }
            else {
                cout << "Root folder not found.\n";
            }
            break;

        case 4: 
            if (xmlParser.getRoot() != nullptr) {
                cout << "Pruning the tree to remove empty folders\n";
                xmlParser.pruneEmptyFolders(xmlParser.getRoot());
                cout << "Tree pruned successfully.\n";
            }
            else {
                cout << "Root folder not found.\n";
            }
            break;
        
        case 5:
            
            if (xmlParser.getRoot() != nullptr) {
                cout << "Enter the name of the File/Folder to find: ";
                string itemName;
                cin >> itemName;

                Tree<File*>* foundNode = xmlParser.findItem(itemName, xmlParser.getRoot(), "");

                if (foundNode != nullptr) {
                    cout << "File/Folder found: " << foundNode->getData()->name << endl;
                }
                else {
                    cout << "File/Folder not found." << endl;
                }
            }
            else {
                cout << "Root folder not found.\n";
            }

            break;  

        case 6:
            if (xmlParser.getRoot() != nullptr) {
                cout << "Enter the name of the folder to display its contents: ";
                string folderName;
                cin >> folderName;

                Tree<File*>* folderNode = xmlParser.findItem(folderName, xmlParser.getRoot());

                if (folderNode != nullptr && folderNode->getData()->type == "dir") {
                    xmlParser.displayFolderContents(folderNode);
                }
                else {
                    cout << "Invalid folder name or not a folder." << endl;
                }
            }
            else {
                cout << "Root folder not found." << endl;
            }

            break;

        case 7:
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}




