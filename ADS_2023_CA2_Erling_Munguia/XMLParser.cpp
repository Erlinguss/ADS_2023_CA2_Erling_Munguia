#include "XMLParser.h"
#include "Tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <SFML/Graphics.hpp>
#include "SFML/Graphics.hpp"


// ===== Function to print the tree structure =====
void printTree(Tree<string>* node, int level = 0) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }
    cout << node->data << endl;

    DListIterator<Tree<string>*> childIter = node->children->getIterator();
    while (childIter.isValid()) {
        printTree(childIter.item(), level + 1);
        childIter.advance();
    }
}

// ========= Implementation of XMLParser ============
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
                else {
                    tagStack.push(tag);
                }
            }
            i = end;
        }
    }

    return tagStack.empty() && hasRoot;
}

// ============== Built XML Tree =====================
void XMLParser::builtTree(const string& xmlDocument) {
    stack<Tree<string>*> nodeStack;

    for (size_t i = 0; i < xmlDocument.size(); ++i) {
        if (xmlDocument[i] == '<') {
            size_t start = i + 1;
            size_t end = xmlDocument.find('>', start);
            if (end == string::npos) {
                return;
            }

            string tag = xmlDocument.substr(start, end - start);
            if (tag.empty()) {
                return;
            }

            if (tag[0] != '/') {

                Tree<string>* newNode = new Tree<string>(tag);
                if (!nodeStack.empty()) {
                    Tree<string>* parent = nodeStack.top();
                    parent->children->append(newNode);
                    newNode->parent = parent;
                }
                else {
                    root = newNode;
                }
                nodeStack.push(newNode);
            }
            else {
                nodeStack.pop();
            }

            i = end;
        }
    }
}

XMLParser::XMLParser(const string& xmlFileName) : xmlFileName(xmlFileName), root(nullptr) {}




int main() {
    const std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia/ADS_2023_CA2_Erling_Munguia/Example.xml";
    XMLParser xmlParser(xmlFileName); 
    xmlParser.parse(); 
    // XMLParser builtTree(const string & xmlDocument);
   
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
