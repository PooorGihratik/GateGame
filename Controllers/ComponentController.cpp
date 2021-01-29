//
// Created by Кир on 17.01.2021.
//

#include "ComponentController.h"
#include "ConnectionControllers/ConnectionsController.h"
#include "Commands/Command.h"

#define InitList component(component), field(field), window(window) ,color(color)
#define ConstructorParams Component *component, ComponentFieldController *field, RenderWindow* window, Color color

#define CharacterSize 15
#define TextPadding 10
#define BrightColor Color(30,30,30)

ComponentController::ComponentController(ConstructorParams)  : InitList {
    auto wires = component->getWires();
    auto connectors = component->getConnectors();
    float tempLength = ConnectionDistance;
    for (int i = 0; i<component->getCountOfInputs();i++) {
        wireControllers.push_back(new ComponentWireController(this,&*wires));
        tempLength += 2 * ConnectionRadius + ConnectionDistance;
        wires++;
    }
    float width = tempLength;
    tempLength = ConnectionDistance;
    for (int i = 0; i<component->getCountOfOutputs();i++) {
        connectorControllers.push_back(new ComponentConnectorController(this,&*connectors));
        tempLength += 2 * ConnectionRadius + ConnectionDistance;
        connectors++;
    }
    width = width >= tempLength ? width : tempLength;
    width = width >= 2 * CharacterSize + 2 * TextPadding ? width : 2 * CharacterSize + TextPadding;
    if (!font.loadFromFile(R"(D:\CLionProjects\GateGame\resources\fonts\20339.ttf)"))
    {
        cout << "fonts dont loaded" << endl;
    }
    text = Text(component->getName(),font,CharacterSize);
    text.setFillColor(sf::Color::White);
    float length = 2*TextPadding + text.getLocalBounds().width;
    size = Vector2f(length, width);
    shape = RectangleShape(size);
    shape.setFillColor(color);
}

ComponentController::~ComponentController() {
    for (int i = 0; i<component->getCountOfInputs();i++) {
        delete wireControllers.back();
        wireControllers.pop_back();
    }
    for (int i = 0; i<component->getCountOfOutputs();i++) {
        delete connectorControllers.back();
        connectorControllers.pop_back();
    }
}

void ComponentController::checkEvents(Event event) {
    if (isBlocked) return;
    for (auto input : wireControllers) {
        input->checkEvents(event);
    }
    for (auto output : connectorControllers) {
        output->checkEvents(event);
    }
    switch (event.type) {
        case sf::Event::MouseButtonReleased:
            if (isDragged) {
                isDragged = false;
                if (field->isInsideField(renderPosition, size)) {
                    field->setCommand(new MoveComponent(this, renderPosition.x, renderPosition.y));
                    field->lostFocusEvent();
                }
                else {
                    field->setCommand(new RemoveComponentFromField(field, this));
                    field->lostFocusEvent();
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (mouseHover && event.mouseButton.button == sf::Mouse::Left) {
                isDragged = true;
                field->componentFocusEvent(this);
            }
            break;
    }
    if (event.type == sf::Event::MouseMoved) {
        Vector2f mouseMotion = Vector2f(event.mouseMove.x,event.mouseMove.y);
        mouseHover = isInside(mouseMotion, Vector2f(0, 0));
        if (isDragged) {
            renderPosition = mouseMotion;
        }
    }
}

void ComponentController::block() {
    isBlocked = true;
}

void ComponentController::unblockAll() {
    isBlocked = false;
    for ( auto wireController : wireControllers ) {
        wireController->unblock();
    }
    for ( auto connectorController : connectorControllers ) {
        connectorController->unblock();
    }
}

void ComponentController::blockWires() {
    for ( auto wireController : wireControllers ) {
        wireController->block();
    }
}

void ComponentController::blockConnectors() {
    for ( auto connectorController : connectorControllers ) {
        connectorController->block();
    }
}

void ComponentController::gotConnectorFocus(IConnectorController* connector) {
    field->connectorFocusEvent(connector);
    for ( auto connectorController : connectorControllers ) {
        if (connectorController == connector) connectorController->unblock();
    }
}

void ComponentController::gotWireFocus(IWireController* wire) {
    field->wireFocusEvent(wire);
    for ( auto wireController : wireControllers ) {
        if (wire == wireController) wireController->unblock();
    }
}

void ComponentController::render() {
    for (auto input : wireControllers) {
        input->render();
    }
    for (auto output : connectorControllers) {
        output->render();
    }

    if (isDragged) {
        Color temp = color;
        temp.a -= 40;
        if (field->isInsideField(renderPosition, size)) temp.r += 20;
        shape.setFillColor(temp);
        shape.setPosition(renderPosition);
    }
    else if (mouseHover) {
        Color temp = color;
        temp += BrightColor;
        shape.setFillColor(temp);
        shape.setPosition(renderPosition);
    }
    else {
        shape.setFillColor(color);
        shape.setPosition(renderPosition);
    }

    text.setPosition(renderPosition.x + TextPadding,renderPosition.y + TextPadding);
    window->draw(shape);
    window->draw(text);
    for ( auto wireController : wireControllers ) {
        wireController->render();
    }
    for ( auto connectorController : connectorControllers ) {
        connectorController->render();
    }
}

