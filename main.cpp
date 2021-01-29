#include <iostream>
#include "Controllers/GameWindow.h"

using namespace sf;

int main() {

    GameWindow window;
    window.init();

    /*float ySize = 1080, xSize = 1920;
    float squareSize = 60;
    float radius = 10;
    bool isDraggable = false;
    bool isDragged = false;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Ya ebal tvou sobaku", sf::Style::Default, settings);


    Vector2f size(800,600);
    Vector2f position(0,0);
    RectangleShape field = RectangleShape(size);
    field.setFillColor(Color(207, 207, 207));
    field.setPosition(position);

    RectangleShape list = RectangleShape(Vector2f(200,600));
    list.setFillColor(Color(130,130,130));
    list.setPosition(800,0);

    sf::Font font;
    if (!font.loadFromFile("D:\\CLionProjects\\GateGame\\resources\\fonts\\20339.ttf"))
    {
        cout << "loz" << endl;
    }

    Text text = Text("AND",font,20);
    text.setFillColor(sf::Color::White);
    text.setPosition(20,20);

    sf::CircleShape point1(radius);
    Vector2f point1pos(20,20);
    point1.setPosition(point1pos);
    point1.setFillColor(Color::Blue);

    sf::CircleShape point2(radius);
    Vector2f point2pos(140, 130);
    point2.setPosition(point2pos);
    point2.setFillColor(Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    break;
                case sf::Event::MouseMoved:
                    break;
            }
        }
        if (isDragged) {

            isDragged = true;
        }

        window.clear();
        window.draw(field);
        window.draw(list);
        //window.draw(point1);
        //window.draw(point2);
        window.draw(text);
        window.display();
    }
*/
    return 0;
}