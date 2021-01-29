//
// Created by Кир on 21.01.2021.
//

#include "ComponentController.h"
#include "ComponentListElement.h"
#include "Commands/Command.h"

#define ConstructorParams GameWindow *window, ComponentFieldController *field
#define InitList field(field), factory(field->getFactory()), window(window)
#define Padding 20

ComponentListController::ComponentListController(ConstructorParams) : InitList {
    position = Vector2f(-1,-1);
    size = Vector2f(-1,-1);
}

bool ComponentListController::hasSizeAndPosition() {
    return position != Vector2f(-1,-1) && size != Vector2f(-1,-1);
}

void ComponentListController::setSize(float x, float y) {
    size = Vector2f(x,y);
    if (hasSizeAndPosition()) {
        auto iter = factory->getIterator();
        float elY = position.y, elX = position.x;
        for (int i = 0;i<factory->getCountOfComponents();i++) {
            IController* element = new ComponentListElement(*iter++,this,i);
            controllers.push_back(element);
            elY += Padding;
            elX = Padding > ( size.x - element->getSizeX() ) / 2 ? position.x + Padding : position.x + ( size.x - element->getSizeX() ) / 2;
            element->setPosition(elX,elY);
            elY += element->getSizeY();
        }
    }
}

void ComponentListController::setPosition(float x, float y) {
    position = Vector2f(x,y);
    if (hasSizeAndPosition()) {
        auto iter = factory->getIterator();
        float elY = position.y, elX = position.x;
        for (int i = 0;i<factory->getCountOfComponents();i++) {
            IController* element = new ComponentListElement(*iter++,this,i);
            controllers.push_back(element);
            elY += Padding;
            elX = Padding > ( size.x - element->getSizeX() ) / 2 ? position.x + Padding : position.x + ( size.x - element->getSizeX() ) / 2;
            element->setPosition(elX,elY);
            elY += element->getSizeY();
        }
    }
}

void ComponentListController::checkWindowEvents(sf::Event event) {
    for (auto controller:controllers) {
        controller->checkWindowEvents(event);
    }
}

void ComponentListController::render() {
    RectangleShape shape = RectangleShape(size);
    shape.setFillColor(Color(130,130,130));
    shape.setPosition(position);
    window->getWindow()->draw(shape);
    for (auto controller:controllers) {
        controller->render();
    }
}

void ComponentListController::setAddCommand(Color color, Vector2f pos, Component* cmp) {
    IComponentController* component = new ComponentController(cmp,field,field->getWindow(),color);
    window->setCommand(new AddComponentToField(field,component,pos.x,pos.y));
}