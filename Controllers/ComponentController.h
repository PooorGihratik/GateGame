//
// Created by Кир on 17.01.2021.
//

#ifndef PROJECT_COMPONENTCONTROLLER_H
#define PROJECT_COMPONENTCONTROLLER_H

#include <list>
#include "../Abstractions/Abstractions.h"
#include "ComponentFieldController.h"

class ComponentController : public IComponentController {
private:
    IComponent* component;
    ComponentFieldController* controller;
    list<IWireController*> wireControllers;
    list<IConnectorController*> connectorControllers;
    bool isBlocked = false;
    bool hasConnectionFocus = false;
    Vector2f position;
    Vector2f size;
    Vector2f bufferPosition;
public:
    ComponentController(IComponent* component, ComponentFieldController* field, Vector2f position);
    ~ComponentController() override;

    void checkEvents(Event event, bool WireBlock, bool ConnectorBlock) override;
    void gotFocus();
    void lostFocus();
    void block() override;
    void unblock() override;
    void render() override;
    void setPosition(float x, float y) override { position = Vector2f(x,y); }
    float getPositionX() override { return bufferPosition.x; }
    float getPositionY() override { return bufferPosition.y; }
    IComponent* getComponent() override { return component; }

    void gotWireFocus(IWireController* wire);
    void gotConnectorFocus(IConnectorController* connector);
};

#endif //PROJECT_COMPONENTCONTROLLER_H
