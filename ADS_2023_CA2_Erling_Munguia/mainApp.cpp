
#include "DList.h"
#include "DListIterator.h"
#include "Tree.h"
#include "structure.h"
#include "TreeIterator.h"
#include "XMLParser.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

const int WindowWidth = 800;
const int WindowHeight = 600;
const int ButtonWidth = 150;
const int ButtonHeight = 40;

sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Data Structure Management");

void drawNode(sf::RenderWindow& window, File* file, float x, float y) {


    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);
    window.draw(circle);


    sf::Font font;
    font.loadFromFile("C:/going-to-do-great-things/goingtodogreatthings.ttf");
    sf::Text text(file->name, font, 14);
    text.setPosition(x + 5, y + 5);
    window.draw(text);
}

void drawTreeRecursive(sf::RenderWindow& window, Tree<File*>* root, float x, float y, float xOffset) {
    if (root != nullptr) {
        drawNode(window, root->getData(), x, y);

        float childX = x - xOffset;
        float childY = y + 80;

        DListIterator<Tree<File*>*> childIter = root->children.getIterator();
        while (childIter.isValid()) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(x + 20, y + 20);
            line[1].position = sf::Vector2f(childX + 20, childY + 20);
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;

            window.draw(line);

            drawTreeRecursive(window, childIter.item(), childX, childY, xOffset / 2);
            childIter.advance();
            childX += xOffset;
        }
    }
}

sf::FloatRect calculateTreeBounds(Tree<File*>* root, float x, float y, float xOffset) {
    sf::FloatRect bounds(x, y, 40, 40);

    if (root != nullptr) {
        float childX = x - xOffset;
        float childY = y + 80;

        DListIterator<Tree<File*>*> childIter = root->children.getIterator();
        while (childIter.isValid()) {
            sf::FloatRect childBounds = calculateTreeBounds(childIter.item(), childX, childY, xOffset / 2);
            bounds.left = std::min(bounds.left, childBounds.left);
            bounds.top = std::min(bounds.top, childBounds.top);
            bounds.width = std::max(bounds.width, childBounds.left + childBounds.width);
            bounds.height = std::max(bounds.height, childBounds.top + childBounds.height);

            childIter.advance();
            childX += xOffset;
        }
    }

    return bounds;
}



void drawTree(sf::RenderWindow& window, const XMLParser& xmlParser) {
    if (xmlParser.getRoot() != nullptr) {
        float centerX = static_cast<float>(window.getSize().x) / 2.0f;
        float centerY = static_cast<float>(window.getSize().y) / 2.0f;

        sf::FloatRect treeBounds = calculateTreeBounds(xmlParser.getRoot(), centerX, centerY, WindowWidth / 4);

        float minWidth = 200.0f;
        float minHeight = 200.0f;

        sf::View view(sf::FloatRect(0, 0, std::max(treeBounds.width + 20, minWidth), std::max(treeBounds.height + 20, minHeight)));
        view.setCenter(centerX, centerY);

        window.setView(view);

        drawTreeRecursive(window, xmlParser.getRoot(), centerX, centerY, WindowWidth / 4);
    }
    else {
        sf::Font font;
        font.loadFromFile("C:/going-to-do-great-things/goingtodogreatthings.ttf");

        sf::Text errorText("Error: Root node not found", font, 20);
        errorText.setPosition(10, 200);
        errorText.setFillColor(sf::Color::Red);

        window.draw(errorText);
    }
}


void drawGUI() {
    window.clear(sf::Color::White);

    sf::Font font;
    if (!font.loadFromFile("C:/going-to-do-great-things/goingtodogreatthings.ttf")) {
        std::cout << "Error loading font!\n";
    }

    // ====Draw button 1====
    sf::RectangleShape button1(sf::Vector2f(ButtonWidth, ButtonHeight));
    button1.setFillColor(sf::Color::Green);
    button1.setPosition(10, 10);
    window.draw(button1);

    // ====Draw button 2====
    sf::RectangleShape button2(sf::Vector2f(ButtonWidth, ButtonHeight));
    button2.setFillColor(sf::Color::Blue);
    button2.setPosition(10, 60);
    window.draw(button2);
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

                if (buttonBounds1.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 1 Clicked!\n" << std::endl;

                    // ===== validate XML, build and display the tree ======
                    std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia_Urbina/ADS_2023_CA2_Erling_Munguia_Urbina/Example1.xml";
                    xmlParser = XMLParser(xmlFileName);
                    xmlParser.parse();
                }
                else if (buttonBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::cout << "Button 2 Clicked!\n" << std::endl;

                    // ===== display the number of items in a folder directory. =====
                    if (xmlParser.getRoot() != nullptr) {
                        std::cout << "Number of items (File/Folder): " << xmlParser.getRoot()->count() << std::endl;
                    }
                    else {
                        std::cout << "Root folder not found.\n";
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
        handleEvent(xmlParser);
        drawGUI();
        drawTree(window, xmlParser);
        window.display();
    }

    return 0;
}