#include <SFML/Graphics.hpp>
#include <iostream>
#include "Core/KeyGenerator.h"

using namespace sf;

int main() {
    float ySize = 1080, xSize = 1920;
    float squareSize = 60;
    float radius = 10;
    bool isDraggable = false;
    bool isDragged = false;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "PIZDEEEEES", sf::Style::Fullscreen, settings);
    sf::RectangleShape shape(sf::Vector2f(squareSize, squareSize));

    sf::CircleShape point1(radius);
    point1.setPosition(20, 20);
    point1.setFillColor(Color::Blue);

    sf::CircleShape point2(radius);
    point2.setPosition(140, 130);
    point2.setFillColor(Color::Blue);

    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(1.0f, 1.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (isDragged) isDragged = false;
                    else if (isDraggable && event.mouseButton.button == sf::Mouse::Left) isDragged = true;
                    break;
                case sf::Event::MouseMoved:
                    bool isXInside = event.mouseMove.x >= shape.getPosition().x &&
                                     event.mouseMove.x <= shape.getPosition().x + squareSize;
                    bool isYInside = event.mouseMove.y >= shape.getPosition().y &&
                                     event.mouseMove.y <= shape.getPosition().y + squareSize;
                    isDraggable = (isXInside && isYInside);
                    break;
            }
        }
        if (isDragged) {
            shape.setPosition(sf::Mouse::getPosition(window).x - squareSize / 2,
                              sf::Mouse::getPosition(window).y - squareSize / 2);
            isDragged = true;
        }

        window.clear();
        window.draw(shape);
        window.draw(point1);
        window.draw(point2);
        window.display();
    }

    return 0;
}