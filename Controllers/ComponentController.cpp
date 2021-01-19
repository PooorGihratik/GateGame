//
// Created by Кир on 17.01.2021.
//

#include "ComponentController.h"
#include "ConnectionControllers/ConnectionsController.h"

#define InitList component(component), controller(field), position(position)
#define ConstructorParams IComponent *component, ComponentFieldController *field,Vector2f position

ComponentController::ComponentController(ConstructorParams)  : InitList {
    Wire* wires = component->getWires();
    Connector* connectors = component->getConnectors();
    for (int i = 0; i<component->getCountOfInputs();i++) {
        wireControllers.push_back(new ComponentWireController(this,wires));
        wires++;
    }
    for (int i = 0; i<component->getCountOfOutputs();i++) {
        connectorControllers.push_back(new ComponentConnectorController(this,connectors));
        connectors++;
    }
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

void ComponentController::checkEvents(Event event, bool WireBlock, bool ConnectorBlock) {
    if (isBlocked) return;
    if (hasConnectionFocus) {
        WireBlock = false;
        ConnectorBlock = false;
    }
    if (!WireBlock) {
        for (auto input : wireControllers) {
            input->checkEvents(event,ConnectorBlock);
        }
    }
    if (ConnectorBlock) return;
    for (auto output : connectorControllers) {
        output->checkEvents(event,WireBlock);
    }
    if (WireBlock || hasConnectionFocus) return;
    // TODO Make event behaviour
}

void ComponentController::gotFocus() {
    controller->gotFocus();
    controller->componentFocusEvent(this);
}

void ComponentController::lostFocus() {
    controller->lostFocus();
    controller->lostFocusEvent();
    for ( auto wireController : wireControllers ) {
        wireController->unblock();
    }
    for ( auto connectorController : connectorControllers ) {
        connectorController->unblock();
    }
    hasConnectionFocus = false;
}

void ComponentController::block() {
    isBlocked = true;
}

void ComponentController::unblock() {
    isBlocked = false;
}

void ComponentController::gotConnectorFocus(IConnectorController* connector) {
    controller->gotFocus();
    controller->connectorFocusEvent();
    hasConnectionFocus = true;
    for ( auto connectorController : connectorControllers ) {
        if (connectorController != connector) connectorController->block();
    }
}

void ComponentController::gotWireFocus(IWireController* wire) {
    controller->gotFocus();
    controller->wireFocusEvent();
    hasConnectionFocus = true;
    for ( auto wireController : wireControllers ) {
        if (wire != wireController) wireController->block();
    }
}

void ComponentController::render() {
    for (auto input : wireControllers) {
        input->render();
    }
    for (auto output : connectorControllers) {
        output->render();
    }
    // TODO create Render for Component
}