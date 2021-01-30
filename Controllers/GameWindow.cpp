//
// Created by Кир on 17.01.2021.
//

#include "GameWindow.h"
#include "ComponentFieldController.h"
#include "ComponentListController.h"

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
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new RenderWindow(sf::VideoMode::getDesktopMode(), "GateGame",sf::Style::Default, settings);

    ComponentFieldController field(this);
    ComponentListController list(this, &field);

    field.setPosition(0,0);
    field.setSize(800,600);

    list.setPosition(800,0);
    list.setSize(200,600);

    controllerList.push_back(&field);
    controllerList.push_back(&list);

    while(window->isOpen()) updateLoop();
}

void GameWindow::updateLoop() {
    Event event;
    while(window->pollEvent(event)) {
        if (event.type == Event::Closed) window->close();
        checkWindowEvents(event);
    }
    if (command != nullptr) {
        command->execute();
        delete command;
        command = nullptr;
    }
    window->clear();
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
