#include "DList.h"
#include "DListIterator.h"
#include "Tree.h"
#include "structure.h"
#include "TreeIterator.h"
#include "XMLParser.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>

const int WindowWidth = 1800;
const int WindowHeight = 1200;
const int BottomWidth = 170;
const int BottomHeight = 40;
const float ScrollSpeed = 100.0f;


sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Data Structure Management");
sf::Font font;


void drawText(sf::RenderWindow& window, const File& file, float x, float y, float scaleFactor, int depth, const std::string& currentDir, sf::Font& font) {
    std::string indentation = std::string(depth * 2, ' ');
    std::string text;

    if (file.type == "dir") {
        text = indentation + "[" + file.name + "]";
    }
    else {
        text = indentation + file.name + (!currentDir.empty() ? "(" + std::to_string(file.size) + ")" + file.type + " " : "");
    }

    sf::Text sfText(text, font, 14 * scaleFactor);
    sfText.setPosition(x, y);
    sfText.setFillColor(sf::Color::Black);
    window.draw(sfText);
}


float drawTreeLabelsRecursive(sf::RenderWindow& window, Tree<File*>* root, float x, float y, float yOffset, float scaleFactor, int depth = 0, const std::string& currentDir = "") {
    if (root != nullptr) {
        float adjustedX = x + depth * 10 * scaleFactor;

        std::string currentPath = currentDir + "/" + root->getData()->name;

        drawText(window, *(root->getData()), adjustedX, y, scaleFactor, depth, currentPath, font);

        float childY = y + yOffset * scaleFactor;

        DListIterator<Tree<File*>*> childIter = root->children.getIterator();
        while (childIter.isValid()) {
            childY = drawTreeLabelsRecursive(window, childIter.item(), adjustedX, childY, yOffset, scaleFactor, depth + 1, currentPath);
            childY += 10 * scaleFactor;
            childIter.advance();
        }

        return childY;
    }

    return y;
}


void drawBottoms() {
    sf::RectangleShape bottom1(sf::Vector2f(BottomWidth, BottomHeight));
    bottom1.setFillColor(sf::Color::Green);
    bottom1.setPosition(10, 10);
    window.draw(bottom1);

    sf::Text title1("Data Structure", font, 25);
    title1.setPosition(10 + (BottomWidth - title1.getLocalBounds().width) / 2, 10 + (BottomHeight - title1.getLocalBounds().height) / 2);
    title1.setFillColor(sf::Color::Black);
    window.draw(title1);

    sf::RectangleShape bottom2(sf::Vector2f(BottomWidth, BottomHeight));
    bottom2.setFillColor(sf::Color::Green);
    bottom2.setPosition(10, 60);
    window.draw(bottom2);

    sf::Text title2("Number of Folders", font, 25);
    title2.setPosition(10 + (BottomWidth - title2.getLocalBounds().width) / 2, 60 + (BottomHeight - title2.getLocalBounds().height) / 2);
    title2.setFillColor(sf::Color::Black);
    window.draw(title2);

    sf::RectangleShape bottom3(sf::Vector2f(BottomWidth, BottomHeight));
    bottom3.setFillColor(sf::Color::Green);
    bottom3.setPosition(10, 120);
    window.draw(bottom3);

    sf::Text title3("Memory Usage", font, 25);
    title3.setPosition(10 + (BottomWidth - title3.getLocalBounds().width) / 2, 120 + (BottomHeight - title3.getLocalBounds().height) / 2);
    title3.setFillColor(sf::Color::Black);
    window.draw(title3);

    sf::RectangleShape bottom4(sf::Vector2f(BottomWidth, BottomHeight));
    bottom4.setFillColor(sf::Color::Green);
    bottom4.setPosition(10, 180);
    window.draw(bottom4);

    sf::Text title4("Prune Empty folders", font, 25);
    title4.setPosition(10 + (BottomWidth - title4.getLocalBounds().width) / 2, 180 + (BottomHeight - title4.getLocalBounds().height) / 2);
    title4.setFillColor(sf::Color::Black);
    window.draw(title4);

    sf::RectangleShape bottom5(sf::Vector2f(BottomWidth, BottomHeight));
    bottom5.setFillColor(sf::Color::Red);
    bottom5.setPosition(10, 300);
    window.draw(bottom5);

    sf::Text title5("Close", font, 25);
    title5.setPosition(10 + (BottomWidth - title5.getLocalBounds().width) / 2, 300 + (BottomHeight - title5.getLocalBounds().height) / 2);
    title5.setFillColor(sf::Color::Black);
    window.draw(title5);

}


void drawInfo(const std::string& info, float x, float y, float scaleFactor, bool isFirstBottomClicked) {
    static std::string infoBottom1;
    static std::string infoBottom2;
    static std::string infoBottom3;
    static std::string infoBottom4;

    if (isFirstBottomClicked) {
        infoBottom1 = info;
    }
    else {
        infoBottom2 = info;
    }

    sf::Text sfText(info, font, 14 * scaleFactor);
    sfText.setPosition(x, y);
    sfText.setFillColor(sf::Color::Black);

    if (isFirstBottomClicked) {
        window.draw(sfText);
    }
    else {
        window.draw(sfText);
    }
}

void drawSearchBox(sf::RenderWindow& window, sf::Text& searchInput, sf::RectangleShape& searchBox, bool isSearchActive) {
    if (isSearchActive) {
        window.draw(searchBox);
        window.draw(searchInput);
    }
}


bool handleEvent(XMLParser& xmlParser, float& yOffset, std::string& infoToDisplay, bool& isFirstBottomClicked, bool& isSearchActive, sf::Text& searchInput, sf::RectangleShape& searchBox) {

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return false;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                sf::FloatRect bottomBounds1(10, 10, BottomWidth, BottomHeight);
                sf::FloatRect bottomBounds2(10, 60, BottomWidth, BottomHeight);
                sf::FloatRect bottomBounds3(10, 120, BottomWidth, BottomHeight);
                sf::FloatRect bottomBounds4(10, 180, BottomWidth, BottomHeight);
                sf::FloatRect bottomBounds5(10, 300, BottomWidth, BottomHeight);

                if (bottomBounds1.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia_Urbina/ADS_2023_CA2_Erling_Munguia_Urbina/Example1.xml";
                    xmlParser = XMLParser(xmlFileName);
                    xmlParser.parse();
                    infoToDisplay = "Data Structure from XML file";
                    isFirstBottomClicked = true;
                }
                else if (bottomBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    if (xmlParser.getRoot() != nullptr) {
                        int itemCount = xmlParser.getRoot()->count();
                        std::cout << "Number of items (File/Folder): " << itemCount << std::endl;
                        infoToDisplay = "Number of items (File/Folder):   " + std::to_string(itemCount);
                    }
                    else {
                        std::cout << "Root folder not found.\n";
                        infoToDisplay = "Root folder not found.";
                    }
                    isFirstBottomClicked = false;
                }

                else if (bottomBounds3.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    if (xmlParser.getRoot() != nullptr) {
                        int memory = xmlParser.memoryUsageBFS(xmlParser.getRoot());
                        std::cout << "Memory used by the folder: " << memory << " bytes\n";
                        infoToDisplay = "Memory used by the folder:     " + std::to_string(memory);
                    }
                    else {
                        std::cout << "Root folder not found.\n";
                        infoToDisplay = "Root folder not found.";
                    }
                    isFirstBottomClicked = false;
                }

                else if (bottomBounds4.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {

                    if (xmlParser.getRoot() != nullptr) {
                        std::cout << "Pruning the tree to remove empty folders\n";
                        xmlParser.pruneEmptyFolders(xmlParser.getRoot());

                        infoToDisplay = "Pruning the tree to remove empty folders. Check number of folders.";
                    }
                    else {
                        std::cout << "Root folder not found.\n";
                    }
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && isSearchActive) {
                    std::string itemName = searchInput.getString().toAnsiString();

                    Tree<File*>* foundNode = xmlParser.findItem(itemName, xmlParser.getRoot(), "");

                    if (foundNode != nullptr) {
                        std::cout << "File/Folder found: " << foundNode->getData()->name << std::endl;
                        infoToDisplay = "File/Folder found: " + foundNode->getData()->name;
                    }
                    else {
                        std::cout << "File/Folder not found." << std::endl;
                        infoToDisplay = "File/Folder not found.";
                    }


                    searchInput.setString("");
                    isSearchActive = false;
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && isSearchActive) {

                    std::string itemName = searchInput.getString().toAnsiString();

                    if (xmlParser.getRoot() != nullptr) {
                        Tree<File*>* foundNode = xmlParser.findItem(itemName, xmlParser.getRoot(), "");

                        if (foundNode != nullptr) {
                            //string fullPath =  xmlParser.displayFolderContents(foundNode);
                            // infoToDisplay = "File/Folder found: " + fullPath;
                        }
                        else {
                            std::cout << "File/Folder not found." << std::endl;
                            infoToDisplay = "File/Folder not found.";
                        }


                        searchInput.setString("");
                        isSearchActive = false;
                    }
                }
                else if (bottomBounds5.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Close Button Clicked!\n" << std::endl;
                    window.close();
                }


                else {

                    sf::FloatRect searchBoxBounds = searchBox.getGlobalBounds();
                    isSearchActive = searchBoxBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                }
            }
        }
        else if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                yOffset -= event.mouseWheelScroll.delta * ScrollSpeed;
            }
        }
    }

    return true;
}


void clearWindow() {
    window.clear(sf::Color::White);
}


int main() {

    if (!font.loadFromFile("C:/going-to-do-great-things/goingtodogreatthings.ttf")) {
        std::cout << "Error loading font!\n";
        return 1;
    }

    std::string xmlFileName;
    XMLParser xmlParser("");
    std::string infoToDisplay;
    bool isFirstBottomClicked = false;

    float scaleFactor = 2.0f;
    float yOffset = 0.0f;

    bool isSearchActive = false;

    sf::Text searchInput("", font, 14 * scaleFactor);
    searchInput.setPosition(10, 240);
    searchInput.setFillColor(sf::Color::Black);

    sf::RectangleShape searchBox(sf::Vector2f(BottomWidth, BottomHeight));
    searchBox.setFillColor(sf::Color::Yellow);
    searchBox.setPosition(10, 240);

    while (window.isOpen()) {
        if (!handleEvent(xmlParser, yOffset, infoToDisplay, isFirstBottomClicked, isSearchActive, searchInput, searchBox)) {
            break;
        }

        clearWindow();

        drawBottoms();

        if (isFirstBottomClicked && xmlParser.getRoot() != nullptr) {
            float finalY = drawTreeLabelsRecursive(window, xmlParser.getRoot(), WindowWidth / 7, 200 + yOffset, 20, scaleFactor);
        }

        drawInfo(infoToDisplay, 300, 100, scaleFactor, !isFirstBottomClicked);

        window.draw(searchBox);
        window.draw(searchInput);

        window.display();
    }

    return 0;
}





