//
// Created by Кир on 17.01.2021.
//

#include "GameWindow.h"
#include "Controllers/ComponentFieldController.h"

#define WindowWidth sf::VideoMode::getDesktopMode().width
#define WindowHeight sf::VideoMode::getDesktopMode().height

void GameWindow::gotFocusEvent(IController *p_controller) {
    focusedController = p_controller;
    for (auto &controller : controllerList) {
        if (controller != focusedController) {
            controller->block();
        }
    }
}

void GameWindow::lostFocusEvent() {
    if (focusedController == nullptr) return;
    for (auto controller : controllerList) {
        controller->unblock();
    }
}

void GameWindow::init() {
    ComponentFieldController controller(this,Vector2f(0,0),Vector2f(WindowWidth,WindowHeight));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    window = new RenderWindow(sf::VideoMode::getDesktopMode(), "PIZDEEEEES",sf::Style::Fullscreen, settings);
    while(window->isOpen()) updateLoop();
}

void GameWindow::updateLoop() {
    Event event;
    while(window->pollEvent(event)) {
        checkWindowEvents(event);
    }
    render();
    window->display();
}

void GameWindow::checkWindowEvents(Event event) {
    for (auto &controller : controllerList) {
        controller->checkWindowEvents(event);
    }
}

void GameWindow::render() {
    for (auto &controller : controllerList) {
        controller->render();
    }
}
