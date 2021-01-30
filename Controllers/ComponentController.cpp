//
// Created by Кир on 17.01.2021.
//

#include "ComponentController.h"
#include "ConnectionControllers/ConnectionsController.h"
#include "Commands/Command.h"

#define InitList component(component), field(field), window(window) ,color(color)
#define ConstructorParams Component *component, ComponentFieldController *field, RenderWindow* window, Color color

#define CharacterSize 20
#define TextPadding 14
#define VerticalPadding 7
#define BrightColor Color(30,30,30)

ComponentController::ComponentController(ConstructorParams)  : InitList {
    // Getting iterators for connections
    auto wires = component->getWires();
    auto connectors = component->getConnectors();

    // Calculating width of component
    float tempLength = ConnectionDistance;
    for (int i = 0; i<component->getCountOfInputs();i++) {
        connectorControllers.push_back(new ConnectorController(this,&*connectors, field->getWindow()));
        tempLength += 2 * ConnectionRadius + ConnectionDistance;
        connectors++;
    }
    float width = tempLength;
    tempLength = ConnectionDistance;
    for (int i = 0; i<component->getCountOfOutputs();i++) {
        wireControllers.push_back(new WireController(this,&*wires, field->getWindow()));
        tempLength += ConnectionRadius + ConnectionRadius + ConnectionDistance;
        wires++;
    }
    // Finding the maximum width between 2 sides of Component
    width = width >= tempLength ? width : tempLength;

    if (!font.loadFromFile(R"(D:\CLionProjects\GateGame\resources\fonts\20339.ttf)"))
    {
        cout << "fonts dont loaded" << endl;
    }
    text = Text(component->getName(),font,CharacterSize);
    text.setFillColor(sf::Color::White);
    verticalTextPadding = VerticalPadding;
    // Setting the minimum width, if its too small to contain text
    if (width > text.getLocalBounds().height * 2 + 2 * VerticalPadding ) {
        verticalTextPadding = width - text.getLocalBounds().height * 2;
        verticalTextPadding /= 2;
    }
    else width =  text.getLocalBounds().height*2 + VerticalPadding * 2;
    float length = 2 * TextPadding + text.getLocalBounds().width;

    // Setting relative position of connectors
    float initialDistance = width - 2 * component->getCountOfInputs() * ConnectionRadius - ConnectionDistance * (component->getCountOfInputs() - 1);
    initialDistance /= 2;
    tempLength = initialDistance + ConnectionRadius;
    auto c_iter = connectorControllers.begin();
    for (int i = 0; i<component->getCountOfInputs();i++) {
        (*c_iter)->setRelativePosition(0,tempLength);
        tempLength += ConnectionDistance + 2*ConnectionRadius;
        c_iter++;
    }

    // Setting relative position of wires
    initialDistance = width - 2 * component->getCountOfOutputs() * ConnectionRadius + ConnectionDistance * (component->getCountOfOutputs() - 1);
    initialDistance /= 2;
    tempLength = initialDistance + ConnectionRadius;
    auto w_iter = wireControllers.begin();
    for (int i = 0; i<component->getCountOfOutputs();i++) {
        (*w_iter)->setRelativePosition(length,tempLength);
        tempLength += ConnectionDistance + ConnectionRadius;
        w_iter++;
    }

    size = Vector2f(length, width);
    shape = RectangleShape(size);
    shape.setFillColor(color);
}

ComponentController::~ComponentController() {
    for (int i = 0; i<component->getCountOfOutputs();i++) {
        delete wireControllers.back();
        wireControllers.pop_back();
    }
    for (int i = 0; i<component->getCountOfInputs();i++) {
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
                diff = renderPosition - Vector2f(Mouse::getPosition(*window));
                field->componentFocusEvent(this);
            }
            break;
    }
    if (event.type == sf::Event::MouseMoved) {
        Vector2f mouseMotion = Vector2f(event.mouseMove.x,event.mouseMove.y);
        mouseHover = isInside(mouseMotion, Vector2f(0, 0));
        if (isDragged) {
            renderPosition = mouseMotion + diff;
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

void ComponentController::connectorFocusEvent(IConnectorController* connector) {
    field->connectorFocusEvent(connector);
    for ( auto connectorController : connectorControllers ) {
        if (connectorController == connector) connectorController->unblock();
    }
}

void ComponentController::wireFocusEvent(IWireController* wire) {
    field->wireFocusEvent(wire);
    for ( auto wireController : wireControllers ) {
        if (wire == wireController) wireController->unblock();
    }
}

void ComponentController::render() {
    for (auto input : wireControllers) {
        input->setPosition(renderPosition.x, renderPosition.y);
        input->render();
    }
    for (auto output : connectorControllers) {
        output->setPosition(renderPosition.x, renderPosition.y);
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

    text.setPosition(renderPosition.x + TextPadding,renderPosition.y + verticalTextPadding);
    window->draw(shape);
    window->draw(text);
    for ( auto wireController : wireControllers ) {
        wireController->render();
    }
    for ( auto connectorController : connectorControllers ) {
        connectorController->render();
    }
}

