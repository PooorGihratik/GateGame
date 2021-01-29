//
// Created by Кир on 19.01.2021.
//
#include "ConnectionsController.h"

FieldConnectorController::FieldConnectorController(FieldParam, ConnectorParam) : FieldInit, ConnectorInit {

}

void FieldConnectorController::checkEvents(sf::Event event) {
    if (isBlocked) return;
    // Some logic...
}

void FieldConnectorController::render() {
    // Some logic...
}

void FieldConnectorController::connectToWire(IWireController *wire) {

}
