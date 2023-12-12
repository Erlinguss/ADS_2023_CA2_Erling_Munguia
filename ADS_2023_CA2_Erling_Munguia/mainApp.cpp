
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
const int ButtonWidth = 150;
const int ButtonHeight = 40;
const float ScrollSpeed = 100.0f;

sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Data Structure Management");

void drawText(sf::RenderWindow& window, const File& file, float x, float y, float scaleFactor, int depth, const std::string& currentDir) {
    sf::Font font;
    if (!font.loadFromFile("C:/going-to-do-great-things/goingtodogreatthings.ttf")) {
        std::cout << "Error loading font!\n";
        return;
    }

    std::string indentation = std::string(depth * 2, ' ');
    std::string text;

    if (file.type == "dir") {
        text = indentation + "[" + file.name + "]";
    }
    else {
        if (!currentDir.empty()) {
            text = indentation + file.name + "(" + std::to_string(file.size) + " " + file.type + ")";
        }
        else {
            text = indentation + file.name;
        }
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

        drawText(window, *(root->getData()), adjustedX, y, scaleFactor, depth, currentPath);

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

void drawGUI() {
    window.clear(sf::Color::White);

    // ====Draw button 1====
    sf::RectangleShape button1(sf::Vector2f(ButtonWidth, ButtonHeight));
    button1.setFillColor(sf::Color::Cyan);
    button1.setPosition(10, 10);
    window.draw(button1);

    // ====Draw button 2====
    sf::RectangleShape button2(sf::Vector2f(ButtonWidth, ButtonHeight));
    button2.setFillColor(sf::Color::Cyan);
    button2.setPosition(10, 60);
    window.draw(button2);
}

bool handleEvent(XMLParser& xmlParser, float& yOffset) {
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

                if (buttonBounds1.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 1 Clicked!\n" << std::endl;

                    // ===== validate XML, build and display the tree labels ======
                    std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia_Urbina/ADS_2023_CA2_Erling_Munguia_Urbina/Example1.xml";

                    xmlParser = XMLParser(xmlFileName);
                    xmlParser.parse();
                }
                else if (buttonBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 2 Clicked!\n" << std::endl;

                    // ===== display the number of items in a folder directory. =====
                    if (xmlParser.getRoot() != nullptr) {
                        int itemCount = xmlParser.getRoot()->count();
                        std::cout << "Number of items (File/Folder): " << itemCount << std::endl;
                    }
                    else {
                        std::cout << "Root folder not found.\n";
                    }
                }
            }
        }

        // ==========Scroll functionality============
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                yOffset -= event.mouseWheelScroll.delta * ScrollSpeed;
            }
        }
    }

    return true;
}

int main() {
    std::string xmlFileName;
    XMLParser xmlParser("");

    float scaleFactor = 2.0f;
    float yOffset = 0.0f;

    while (window.isOpen()) {
        handleEvent(xmlParser, yOffset);
        drawGUI();
        float finalY = drawTreeLabelsRecursive(window, xmlParser.getRoot(), WindowWidth / 30, 300 + yOffset, 20, scaleFactor);
        window.display();
    }

    return 0;
}
