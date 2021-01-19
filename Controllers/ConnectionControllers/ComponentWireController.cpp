//
// Created by Кир on 19.01.2021.
//
#include "ConnectionsController.h"

ComponentWireController::ComponentWireController(ComponentParam, WireParam) : ComponentInit, WireInit {

}

void ComponentWireController::checkEvents(sf::Event event, bool ConnectorBlock) {
    if (isBlocked) return;
    // Some logic...
}

void ComponentWireController::render() {
    // Some logic
}

