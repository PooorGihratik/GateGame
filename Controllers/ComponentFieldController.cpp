//
// Created by Кир on 17.01.2021.
//

#include "ComponentFieldController.h"
#include "ComponentController.h"
#include "ConnectionControllers/ConnectionsController.h"
#include <algorithm>

#define ConstructorParams GameWindow *window, Vector2f position, Vector2f size
#define InitList window(window), position(position), size(size)

ComponentFieldController::ComponentFieldController(ConstructorParams) : InitList {

}

void ComponentFieldController::render() {
    if (isBlocked) return;
    for (auto input:inputControllers) {
        input->render();
    }
    for (auto output:outputControllers) {
        output->render();
    }
    for (auto controller:controllers) {
        controller->render();
    }
}

void ComponentFieldController::checkWindowEvents(sf::Event event) {
    if (isBlocked) return;
    for (auto input:inputControllers) {
        input->checkEvents(event,f_connectorBlock);
    }
    for (auto output:outputControllers) {
        output->checkEvents(event,f_wireBlock);
    }
    for (auto controller:controllers) {
        controller->checkEvents(event,f_wireBlock,f_connectorBlock);
    }
}

void ComponentFieldController::componentFocusEvent(IComponentController* component) {
    for (auto &controller:controllers) {
        if (component != controller) controller->block();
    }
    auto iter = find(controllers.begin(), controllers.end(), component);
    swap(iter,--controllers.end());
}

void ComponentFieldController::lostFocusEvent() {
    f_connectorBlock = false;
    f_wireBlock = false;
    for (auto &controller:controllers) {
        controller->unblock();
    }
}

void ComponentFieldController::lostFocus() {
    window->lostFocusEvent();
}

void ComponentFieldController::gotFocus() {
    window->gotFocusEvent(this);
}

// Section for commands

IComponentController* ComponentFieldController::addNewComponent(float x, float y) {
    IComponent* component = network.addComponent();
    IComponentController* controller = new ComponentController(component, this, Vector2f(x,y));
    controllers.push_back(controller);
    return controller;
}

void ComponentFieldController::removeComponent(IComponentController* controller) {
    network.removeComponent(controller->getComponent());
    delete controller;
    controllers.remove(controller);
}

void ComponentFieldController::addInput() {
    Wire* wire = network.addWire();
    inputControllers.push_back(new FieldWireController(this,wire));
}

void ComponentFieldController::removeInput() {
    network.removeWire();
    delete inputControllers.back();
    inputControllers.pop_back();
}

void ComponentFieldController::addOutput() {
    Connector* connector = network.addConnector();
    outputControllers.push_back(new FieldConnectorController(this,connector));
}

void ComponentFieldController::removeOutput() {
    network.removeConnector();
    delete outputControllers.back();
    outputControllers.pop_back();
}
