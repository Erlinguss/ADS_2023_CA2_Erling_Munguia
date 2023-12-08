/*#include <iostream>
#include "XMLParser.h"
#include <SFML/Graphics.hpp>

const int WindowWidth = 800;
const int WindowHeight = 600;
const int ButtonWidth = 150;
const int ButtonHeight = 40;

sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "data Structure Management");

void drawGUI(const XMLParser& xmlParser) {
    window.clear(sf::Color::White);


    // ====Draw button 1 ====
    sf::RectangleShape button1(sf::Vector2f(ButtonWidth, ButtonHeight));
    button1.setFillColor(sf::Color::Green);
    button1.setPosition(10, 10);
    window.draw(button1);

    // ====Draw button 2====
    sf::RectangleShape button2(sf::Vector2f(ButtonWidth, ButtonHeight));
    button2.setFillColor(sf::Color::Blue);
    button2.setPosition(10, 60);
    window.draw(button2);

    // ====Draw button 2====
    sf::RectangleShape button3(sf::Vector2f(ButtonWidth, ButtonHeight));
    button3.setFillColor(sf::Color::Red);
    button3.setPosition(10, 90);
    window.draw(button3);

    // ====Draw button 2====
    sf::RectangleShape button4(sf::Vector2f(ButtonWidth, ButtonHeight));
    button4.setFillColor(sf::Color::Yellow);
    button4.setPosition(10, 120);
    window.draw(button4);

    //====Draw button 2====
    sf::RectangleShape button5(sf::Vector2f(ButtonWidth, ButtonHeight));
    button5.setFillColor(sf::Color::Magenta);
    button5.setPosition(10, 150);
    window.draw(button5);

    // ====Draw button 2====
    sf::RectangleShape button6(sf::Vector2f(ButtonWidth, ButtonHeight));
    button6.setFillColor(sf::Color::Cyan);
    button6.setPosition(10, 180);
    window.draw(button6);

    window.display();
}


bool handleEvent(XMLParser& xmlParser) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return false;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);


                sf::FloatRect buttonBounds1(10, 10, ButtonWidth, ButtonHeight);
                sf::FloatRect buttonBounds2(10, 60, ButtonWidth, ButtonHeight);
                sf::FloatRect buttonBounds3(10, 90, ButtonWidth, ButtonHeight);
                sf::FloatRect buttonBounds4(10, 120, ButtonWidth, ButtonHeight);
                sf::FloatRect buttonBounds5(10, 150, ButtonWidth, ButtonHeight);
                sf::FloatRect buttonBounds6(10, 180, ButtonWidth, ButtonHeight);

               
               
                if (buttonBounds1.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 1 Clicked" << std::endl;

                    // ===== validate XML, build and display the tree ======
                    std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia_Urbina/ADS_2023_CA2_Erling_Munguia_Urbina/Example1.xml";
                    xmlParser = XMLParser(xmlFileName);
                    xmlParser.parse();
                }
                else if (buttonBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 2 Clicked\n" << std::endl;

                    // ===== display the number of items in a folder directory. =====
                    if (xmlParser.getRoot() != nullptr) {
                        std::cout << "Number of items (File/Folder): " << xmlParser.getRoot()->count() << std::endl;
                    }
                    else {
                        std::cout << "Root folder not found.\n";
                    }
                }
                else if (buttonBounds3.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 3 Clicked\n" << std::endl;

                    // ======display the memory used by a given folder ======
                    if (xmlParser.getRoot() != nullptr) {
                        std::cout << "Memory used by the folder: " << xmlParser.memoryUsageBFS(xmlParser.getRoot()) << " bytes\n";
                    }
                    else {
                        std::cout << "Root folder not found.\n";
                    }
                }
                else if (buttonBounds4.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 4 Clicked!\n" << std::endl;

                    // ======= prune the tree to remove empty folders. =======
                    if (xmlParser.getRoot() != nullptr) {
                        std::cout << "Pruning the tree to remove empty folders\n";
                        xmlParser.pruneEmptyFolders(xmlParser.getRoot());
                        std::cout << "Tree pruned successfully.\n";
                    }
                    else {
                        std::cout << "Root folder not found.\n";
                    }
                }
                else if (buttonBounds5.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 5 Clicked!\n" << std::endl;

                    // =======find a given file/folder===========
                    if (xmlParser.getRoot() != nullptr) {
                        std::cout << "Enter the name of the File/Folder to find: ";
                        std::string itemName;
                        std::cin >> itemName;

                        Tree<File*>* foundNode = xmlParser.findItem(itemName, xmlParser.getRoot(), "");

                        if (foundNode != nullptr) {
                            std::cout << "File/Folder found: " << foundNode->getData()->name << std::endl;
                        }
                        else {
                            std::cout << "File/Folder not found." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Root folder not found.\n";
                    }
                }
                else if (buttonBounds6.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 6 Clicked!\n" << std::endl;

                    // ======display the contents of a given folder ======
                    if (xmlParser.getRoot() != nullptr) {
                        std::cout << "Enter the name of the folder to display its contents: ";
                        std::string folderName;
                        std::cin >> folderName;

                        Tree<File*>* folderNode = xmlParser.findItem(folderName, xmlParser.getRoot(), "");
                        if (folderNode != nullptr) {
                            xmlParser.displayFolderContents(folderNode);
                        }
                        else {
                            std::cout << "Invalid folder name or not a folder." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Root folder not found." << std::endl;
                    }
                }

            }
        }
    }

    return true;
}

int main() {
    std::string xmlFileName;
    XMLParser xmlParser("");

    while (window.isOpen()) {

        drawGUI(xmlParser);


        if (!handleEvent(xmlParser)) {
            break;
        }

        window.display();

        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}
*/