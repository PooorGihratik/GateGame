//
// Created by Кир on 30.01.2021.
//

#ifndef GATEGAME_CONNECTIONRENDER_H
#define GATEGAME_CONNECTIONRENDER_H

#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;

class ConnectionRender {
private:
    Vector2f relativePosition;
    Vector2f position;
    CircleShape shape;
    float radius;
    RenderWindow* window;
    bool isActive = false;
    bool mouseHover = false;
public:
    ConnectionRender(RenderWindow* window, float radius);
    void setPosition(Vector2f position);
    void setRelativePosition(Vector2f relative);
    void setState(bool value) { isActive = value; }
    void setMouseHover(bool value) { mouseHover = value; }
    bool isInside(Vector2f point) {
        Vector2f diff = position-point;
        return sqrt(diff.x * diff.x + diff.y * diff.y) < radius;
    }
    void render();
};

#endif //GATEGAME_CONNECTIONRENDER_H
