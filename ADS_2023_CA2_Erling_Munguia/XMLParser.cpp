#include "XMLParser.h"
#include "Tree.h"
#include <SFML/Graphics.hpp>

//#include "SFML/Graphics.hpp"

//int main() {
//    const std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia/ADS_2023_CA2_Erling_Munguia/Example.xml";
//    XMLParser xmlParser(xmlFileName); 
//    xmlParser.parse(); 
   
//    return 0;
//}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}