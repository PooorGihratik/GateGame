//
// Created by Кир on 17.01.2021.
//

#ifndef PROJECT_COMPONENTFIELDCONTROLLER_H
#define PROJECT_COMPONENTFIELDCONTROLLER_H

#include "Abstractions/Abstractions.h"
#include "GameWindow.h"

#define ConnectionRadius 7
#define ConnectionDistance 7


class ComponentFieldController : public IComponentFieldController, public IController, public IConnectionBase {
private:
    list<IComponentController*> controllers;
    list<IWireController*> inputControllers;
    list<IConnectorController*> outputControllers;
    ComponentNetwork network;
    bool isBlocked = false;
    GameWindow* window;
    Vector2f position;
    Vector2f size;

    ICommand* command = nullptr;

    bool hasSizeAndPosition();
public:
    ComponentFieldController(GameWindow* window);

    sf::RenderWindow* getWindow() { return window->getWindow(); }

    void checkWindowEvents(sf::Event event) override;
    float getSizeX() override { return size.x; }
    float getSizeY() override { return size.y; }
    void setPosition(float x, float y) override { position = Vector2f(x,y); }
    void setSize(float x, float y) override { size = Vector2f(x,y); }
    ComponentFactory* getFactory() { return network.getFactory(); }
    void render() override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }

    void wireFocusEvent(IWireController* wire) override;
    void connectorFocusEvent(IConnectorController* connector) override;
    void componentFocusEvent(IComponentController* component);
    void lostFocusEvent();

    bool isInsideField(Vector2f objPos, Vector2f objSize) const {
        bool result = position.x <= objPos.x && position.y <= objPos.y
                      && position.x + size.x >= objPos.x + objSize.x && position.y + size.y >= objPos.y +  objSize.y;
        return result;
    }

    // Command Control Section

    void setCommand(ICommand* command) { window->setCommand(command); }
    ICommand* getCommand() { return command; }

    IComponentController* addNewComponent(IComponentController* controller, float x, float y) override;
    void removeComponent(IComponentController* controller) override;
    void addInput() override;
    void removeInput() override;
    void addOutput() override;
    void removeOutput() override;
};

#endif //PROJECT_COMPONENTFIELDCONTROLLER_H
