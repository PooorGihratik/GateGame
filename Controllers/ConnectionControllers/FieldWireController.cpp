//
// Created by Кир on 19.01.2021.
//

#include "ConnectionsController.h"

FieldWireController::FieldWireController(FieldParam, WireParam) : WireInit, FieldInit {

}

void FieldWireController::checkEvents(sf::Event event, bool ConnectorBlock) {
    if (isBlocked) return;
    // Some logic...
}

void FieldWireController::render() {
    // Some logic...
}