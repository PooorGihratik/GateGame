//
// Created by Кир on 17.01.2021.
//

#include "ComponentController.h"

#define InitList component(component), controller(field), position(position)
#define ConstructorParams IComponent *component, ComponentFieldController *field,Vector2f position

ComponentController::ComponentController(ConstructorParams)  : InitList {

}

void ComponentController::checkEvents(Event event, bool WireBlock, bool ConnectorBlock) {
    if (isBlocked) return;
    if (!WireBlock) {
        for (auto input : wireControllers) {
            input->checkEvents(event,ConnectorBlock);
        }
    }
    if (ConnectorBlock) return;
    for (auto output : connectorControllers) {
        output->checkEvents(event,WireBlock);
    }
    if (WireBlock) return;

}

void ComponentController::gotFocus() {
    controller->gotFocus();
    controller->componentFocusEvent(this);
}

void ComponentController::lostFocus() {
    controller->lostFocus();
    controller->lostFocusEvent();
}

void ComponentController::block() {
    isBlocked = true;
}

void ComponentController::unblock() {
    isBlocked = false;
}

void ComponentController::gotConnectorFocus() {
    controller->gotFocus();
}

void ComponentController::gotWireFocus() {
    controller->gotFocus();
}

void ComponentController::render(float x, float y) {

}