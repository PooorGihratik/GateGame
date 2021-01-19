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
    Vector2f position;
    Vector2f size;
    Vector2f bufferPosition;
public:
    ComponentController(IComponent* component, ComponentFieldController* field, Vector2f position);
    void checkEvents(Event event, bool WireBlock, bool ConnectorBlock) override;
    void gotFocus();
    void lostFocus();
    void block() override;
    void unblock() override;
    void render() override;
    void setPosition(float x, float y) override { position = Vector2f(x,y); }
    Vector2f getPosition() { return bufferPosition; }
    IComponent* getComponent() override { return component; }
    void gotWireFocus();
    void gotConnectorFocus();

};

#endif //PROJECT_COMPONENTCONTROLLER_H
