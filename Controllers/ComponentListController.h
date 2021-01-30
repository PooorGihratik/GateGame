//
// Created by Кир on 21.01.2021.
//

#ifndef GATEGAME_COMPONENTLISTCONTROLLER_H
#define GATEGAME_COMPONENTLISTCONTROLLER_H

#include "Abstractions/Abstractions.h"
#include "GameWindow.h"
#include "ComponentFieldController.h"
#include "../Core/ComponentNetwork.h"


class ComponentListController : public IController {
private:
    ComponentFactory* factory;
    vector<IController*> controllers;
    ComponentFieldController* field;
    GameWindow* window;
    bool isBlocked = false;
    Vector2f position;
    Vector2f size;

    bool hasSizeAndPosition();
public:
    ComponentListController(GameWindow* window,ComponentFieldController* field);
    void setPosition(float x, float y) override;
    void setSize(float x, float y) override;
    float getSizeX() { return size.x; }
    float getSizeY() { return size.y; }
    ComponentFieldController* getController() { return field; }
    Vector2f getPosition() { return position; }
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }
    void gotFocus() { window->gotFocusEvent(this); }
    void lostFocus() { window->lostFocusEvent(); }
    RenderWindow* getWindow() { return window->getWindow(); }
    void render() override;
    void checkWindowEvents(sf::Event event) override;

    void setComponent(int index) { factory->selectComponent(index); }
    void setCommand(ICommand* command) { window->setCommand(command); }
    void setAddCommand(Color color, Vector2f pos, Component* cm);
};

#endif //GATEGAME_COMPONENTLISTCONTROLLER_H
