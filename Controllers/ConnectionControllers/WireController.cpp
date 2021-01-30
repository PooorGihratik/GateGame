//
// Created by Кир on 19.01.2021.
//
#include "ConnectionsController.h"

WireController::WireController(BaseParam, WireParam, RenderWindow *window) : BaseInit, WireInit, RendererInit {

}

void WireController::checkEvents(sf::Event event) {
    if (isBlocked) return;
    switch (event.type) {
        case Event::MouseButtonPressed:
            break;
        case Event::MouseButtonReleased:
            break;
    }
    if (event.type == Event::MouseMoved) {
        Vector2f mouseMove = Vector2f(event.mouseMove.x,event.mouseMove.y);
        if (renderer.isInside(mouseMove)) {

        }
    }
}

void WireController::render() {
    renderer.render();
}

