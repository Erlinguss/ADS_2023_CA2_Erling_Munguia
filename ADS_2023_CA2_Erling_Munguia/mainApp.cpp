
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
const int BottomWidth = 150;
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
        text = indentation + file.name + (!currentDir.empty() ? "(" + std::to_string(file.size) + " " + file.type + ")" : "");
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
    bottom1.setFillColor(sf::Color::Cyan);
    bottom1.setPosition(10, 10);
    window.draw(bottom1);

    sf::RectangleShape bottom2(sf::Vector2f(BottomWidth, BottomHeight));
    bottom2.setFillColor(sf::Color::Cyan);
    bottom2.setPosition(10, 60);
    window.draw(bottom2);

    sf::RectangleShape bottom3(sf::Vector2f(BottomWidth, BottomHeight));
    bottom3.setFillColor(sf::Color::Cyan);
    bottom3.setPosition(10, 120);
    window.draw(bottom3);
}


void drawInfo(const std::string& info, float x, float y, float scaleFactor, bool isFirstBottomClicked) {
    static std::string infoBottom1;
    static std::string infoBottom2;
    static std::string infoBottom3;

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


bool handleEvent(XMLParser& xmlParser, float& yOffset, std::string& infoToDisplay, bool& isFirstBottomClicked) {
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
                sf::FloatRect bottomBounds3(10, 110, BottomWidth, BottomHeight);

                if (bottomBounds1.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia_Urbina/ADS_2023_CA2_Erling_Munguia_Urbina/Example1.xml";
                    xmlParser = XMLParser(xmlFileName);
                    xmlParser.parse();
                    infoToDisplay = "Data Structure from XMl file";
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
            }
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
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

    while (window.isOpen()) {
        if (!handleEvent(xmlParser, yOffset, infoToDisplay, isFirstBottomClicked)) {
            break;
        }

        clearWindow();

        drawBottoms();

        if (isFirstBottomClicked && xmlParser.getRoot() != nullptr) {
            float finalY = drawTreeLabelsRecursive(window, xmlParser.getRoot(), WindowWidth / 7, 200 + yOffset, 10, scaleFactor);
        }

        drawInfo(infoToDisplay, 300, 100, scaleFactor, !isFirstBottomClicked);

        window.display();
    }

    return 0;
}
