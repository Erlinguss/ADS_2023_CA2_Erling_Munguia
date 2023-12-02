#include "XMLParser.h"
#include "Tree.h"
#include "structure.h"
#include "TreeIterator.h"

#include <iostream>
#include <fstream>
#include <sstream>
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
        cout << "Tree structure:" << endl;
        displayTree(TreeIterator<File*>(tree), ""); 
    }
}



int main() {
    const std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia/ADS_2023_CA2_Erling_Munguia/Example1.xml";
    XMLParser xmlParser(xmlFileName); 
    xmlParser.parse(); 

    int choice;

    do {
        cout << "Select an option:\n";
        cout << "1. Determine the number of items within a given folder directory.\n";
        cout << "2. Determine the amount of memory used by a given folder.\n";
        cout << "3. Prune the tree to remove empty folders.\n";
        cout << "4. Find a given file/folder.\n";
        cout << "5. Display the contents of a given folder.\n";
        cout << "0. Exit.\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Call the countItems function
            cout << "Number of items: " << xmlParser.getRoot()->countItems() << endl;
            break;
        case 2:
             break;
        case 3:
           
            break;
        case 4: {
           
            break;
        }
        case 5:
           
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


//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);

 //   while (window.isOpen())
 //   {
  //      sf::Event event;
 //       while (window.pollEvent(event))
 //       {
//            if (event.type == sf::Event::Closed)
 //               window.close();
 //       }

  //      window.clear();
  //      window.draw(shape);
   //     window.display();
  //  }

  //  return 0;
//}


