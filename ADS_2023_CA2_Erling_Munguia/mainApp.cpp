#include <iostream>
#include "XMLParser.h"
#include <SFML/Graphics.hpp>

const int WindowWidth = 800;
const int WindowHeight = 600;
const int ButtonWidth = 150;
const int ButtonHeight = 40;

sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "data Structure Management");

void drawGUI(const XMLParser& xmlParser) {
    window.clear(sf::Color::White);

    sf::RectangleShape button(sf::Vector2f(ButtonWidth, ButtonHeight));
    button.setFillColor(sf::Color::Green);
    button.setPosition(10, 10);
    window.draw(button);

    window.display();
}