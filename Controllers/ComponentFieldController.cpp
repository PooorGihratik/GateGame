//
// Created by Кир on 17.01.2021.
//

#include "ComponentFieldController.h"
#include "ComponentController.h"
#include "ConnectionControllers/ConnectionsController.h"
#include <algorithm>

#define ConstructorParams GameWindow *window
#define InitList window(window)

ComponentFieldController::ComponentFieldController(ConstructorParams) : InitList {
    position = Vector2f(-1,-1);
    size = Vector2f(-1,-1);
}

void ComponentFieldController::render() {
    RectangleShape shape = RectangleShape(size);
    shape.setFillColor(Color(207,207,207));
    shape.setPosition(position);
    window->getWindow()->draw(shape);
    for (auto input:inputControllers) {
        input->render();
    }
    for (auto output:outputControllers) {
        output->render();
    }
    for (auto controller:controllers) {
        controller->render();
    }
    /*auto iter = controllers.end();
    for (int i = 0; i< controllers.size();i++) {
        (*--iter)->render();
    }*/
}

bool ComponentFieldController::hasSizeAndPosition() {
    return position != Vector2f(-1,-1) && size != Vector2f(-1,-1);
}

void ComponentFieldController::checkWindowEvents(sf::Event event) {
    if (isBlocked) return;
    auto iter = controllers.end();
    for (int i = 0; i< controllers.size();i++) {
        (*--iter)->checkEvents(event);
    }
    for (auto input:inputControllers) {
        input->checkEvents(event);
    }
    for (auto output:outputControllers) {
        output->checkEvents(event);
    }
}

void ComponentFieldController::lostFocusEvent() {
    for (auto &controller:controllers) {
        controller->unblockAll();
    }
    window->lostFocusEvent();
}

void ComponentFieldController::componentFocusEvent(IComponentController* component) {
    window->gotFocusEvent(this);
    for (auto &controller:controllers) {
        if (component != controller) controller->block();
    }
    auto iter = find(controllers.begin(), controllers.end(), component);
    swap(*iter,*--controllers.end());
}

void ComponentFieldController::wireFocusEvent(IWireController* wire) {
    window->gotFocusEvent(this);
    for ( auto inputController : inputControllers ) {
        if (inputController != wire) inputController->block();
    }
    for ( auto controller: controllers ) {
        controller -> blockWires();
    }
}

void ComponentFieldController::connectorFocusEvent(IConnectorController* connector) {
    window->gotFocusEvent(this);
    for ( auto outputController : outputControllers ) {
        if (outputController != connector) outputController->block();
    }
    for ( auto controller: controllers ) {
        controller -> blockConnectors();
    }
}

// Section for commands

IComponentController* ComponentFieldController::addNewComponent(IComponentController* controller, float x, float y) {
    Component* component = network.addComponent();
    controller->setComponent(component);
    controller->setPosition(x,y);
    controllers.push_back(controller);
    return controller;
}

void ComponentFieldController::removeComponent(IComponentController* controller) {
    network.removeComponent(controller->getComponent());
    controllers.remove(controller);
    delete controller;
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
