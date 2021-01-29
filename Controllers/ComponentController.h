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
    Component* component;
    ComponentFieldController* field;
    list<IWireController*> wireControllers;
    list<IConnectorController*> connectorControllers;
    RenderWindow* window;
    bool isBlocked = false;
    bool isDragged = false, mouseHover = false;
    Vector2f position;
    Vector2f size;
    Vector2f renderPosition;
    RectangleShape shape;
    Color color;
    Text text;
    Font font;
public:
    ComponentController(Component* component, ComponentFieldController* field, RenderWindow* window, Color color);
    ~ComponentController() override;

    void checkEvents(Event event) override;
    void block() override;
    void unblockAll() override;
    void blockWires() override;
    void blockConnectors() override;
    void render() override;
    void setPosition(float x, float y) override {
        position = Vector2f(x,y);
        renderPosition = position;
    }
    float getPositionX() override { return position.x; }
    float getPositionY() override { return position.y; }

    float getSizeX() override { return size.x; }
    float getSizeY() override { return size.y; }

    Color getColor() { return color; }
    Component* getComponent() override { return component; }
    void setComponent(Component* component) override { this->component = component; }
    ComponentFieldController* getField() { return field; }

    bool isInside(Vector2f objPos, Vector2f objSize) const {
        return position.x <= objPos.x && position.y <= objPos.y
               && position.x+size.x >= objPos.x +  objSize.x && position.y+size.y >= objPos.y +  objSize.y;
    }

    bool isInsideField(Vector2f objPos) {
        return field->isInsideField(objPos,size);
    }

    void gotWireFocus(IWireController* wire);
    void gotConnectorFocus(IConnectorController* connector);

    // TODO Create command pass mechanism
    void setConnectionCommand(ICommand* command) { field->setCommand(command); }
    ICommand* getCommand() { return field->getCommand(); }
};

#endif //PROJECT_COMPONENTCONTROLLER_H
