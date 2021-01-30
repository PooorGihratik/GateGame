//
// Created by Кир on 30.01.2021.
//

#include "ConnectionRender.h"

#define OffColor Color(0,0,0)
#define OnColor Color(0,0,0)

ConnectionRender::ConnectionRender(RenderWindow *window, float radius)  : window(window), radius(radius) {
    shape = CircleShape(radius);
    shape.setFillColor(OffColor);
    position = Vector2f(0,0);
}

void ConnectionRender::setPosition(Vector2f position) {
    this->position = position + relativePosition;
}

void ConnectionRender::setRelativePosition(Vector2f relative) {
    relativePosition = relative;
}

void ConnectionRender::render() {
    shape.setFillColor(isActive? OnColor : OffColor);
    shape.setPosition((position.x - radius),(position.y - radius));
    window->draw(shape);
}