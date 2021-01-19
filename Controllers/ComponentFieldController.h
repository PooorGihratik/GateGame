//
// Created by Кир on 17.01.2021.
//

#ifndef PROJECT_COMPONENTFIELDCONTROLLER_H
#define PROJECT_COMPONENTFIELDCONTROLLER_H

#include "../Abstractions/Abstractions.h"
#include "../GameWindow.h"

#define ConnectionRadius 50

class ComponentFieldController : public IComponentFieldController {
private:
    list<IComponentController*> controllers;
    list<IWireController*> inputControllers;
    list<IConnectorController*> outputControllers;
    ComponentNetwork network;
    bool isBlocked = false;
    bool f_wireBlock = false;
    bool f_connectorBlock = false;
    GameWindow* window;
    Vector2f position;
    Vector2f size;
public:
    ComponentFieldController(GameWindow* window, Vector2f position, Vector2f size);

    void gotFocus();
    void lostFocus();

    void checkWindowEvents(sf::Event event) override;
    void render() override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }

    void wireFocusEvent() { f_wireBlock = true; }
    void connectorFocusEvent() { f_connectorBlock = true; }
    void componentFocusEvent(IComponentController* component);
    void lostFocusEvent();

    // Command Control Section

    IComponentController* addNewComponent(float x, float y) override;
    void removeComponent(IComponentController* controller) override;
    void addInput() override;
    void removeInput() override;
    void addOutput() override;
    void removeOutput() override;
};

#endif //PROJECT_COMPONENTFIELDCONTROLLER_H
