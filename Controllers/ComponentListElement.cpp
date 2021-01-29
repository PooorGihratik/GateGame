//
// Created by Кир on 21.01.2021.
//

#include "ComponentListElement.h"

#define ConstructorParams IComponentLogic *logic, ComponentListController* list, int index
#define InitList logic(logic), list(list), index(index)

ComponentListElement::ComponentListElement(ConstructorParams) : InitList {
    color = Color(rand()%255 + 1,rand()%255 + 1,rand()%255 + 1);
    component = new ComponentController(new Component(logic),list->getController(),list->getWindow(),color);
    renderPosition = position;
    component->setPosition(renderPosition.x, renderPosition.y);
}

ComponentListElement::~ComponentListElement() {
    delete component->getComponent();
    delete component;
}

void ComponentListElement::render() {
    component->setPosition(renderPosition.x,renderPosition.y);
    component->render();
}

void ComponentListElement::checkWindowEvents(Event event) {
    if (isBlocked) return;
    switch (event.type) {
        case sf::Event::MouseButtonReleased:
            if (isDragged) {
                isDragged = false;
                list->lostFocus();
                if (component->isInsideField(renderPosition)) {
                    list->setAddCommand(color, renderPosition, component->getComponent());
                }
                renderPosition = position;
                component->setPosition(renderPosition.x, renderPosition.y);
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left && mouseHover) {
                list->gotFocus();
                list->setComponent(index);
                isDragged = true;
            }
            break;
    }
    if (event.type == sf::Event::MouseMoved) {
        Vector2f mouseMotion = Vector2f(event.mouseMove.x,event.mouseMove.y);
        mouseHover = component->isInside(mouseMotion, Vector2f(0, 0));
        if (isDragged) {
            renderPosition = mouseMotion;
            component->setPosition(renderPosition.x, renderPosition.y);
        }
        else renderPosition = position;
    }
}