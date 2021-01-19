//
// Created by Кир on 18.01.2021.
//

#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H
#include "../ComponentFieldController.h"


class AddComponentToField : public ICommand {
private:
    ComponentFieldController* controller;
    float x, y;
public:
    AddComponentToField(ComponentFieldController* controller, float x, float y);
    void execute() override;
    void undo() override;
};

class RemoveComponentFromField : public ICommand{
private:
    ComponentFieldController* controller;
    IComponentController* component;
public:
    RemoveComponentFromField(ComponentFieldController* controller, IComponentController component);
    void execute() override;
    void undo() override;
};

class MoveComponent : public ICommand {
private:
    IComponentController* component;
    float x,y;
    float bufferX, bufferY;
public:
    MoveComponent(IComponentController* component, float x, float y) : component(component), x(x), y(y) {
        bufferX = x;
        bufferY = y;
    };
    void execute() override;
    void undo() override;
};

class ConnectCommand : public ICommand {
private:
    IWireController* wire = nullptr;
    IConnectorController* connector = nullptr;
public:
    void setWireController(IWireController* controller) { this->wire = controller; }
    void setConnectorController(IConnectorController* controller) { this->connector = controller; }
    bool hasWire() { return wire == nullptr; }
    bool hasConnector() { return connector == nullptr; }
    void execute() override;
    void undo() override;
};


#endif //PROJECT_COMMAND_H
