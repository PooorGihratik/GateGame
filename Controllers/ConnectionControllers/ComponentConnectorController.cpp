//
// Created by Кир on 19.01.2021.
//

#include "ConnectionsController.h"

ComponentConnectorController::ComponentConnectorController(ComponentParam, ConnectorParam) : ComponentInit, ConnectorInit {

}

void ComponentConnectorController::checkEvents(sf::Event event) {
    if (isBlocked) return;

}

void ComponentConnectorController::render() {
    // Some logic...
}

void ComponentConnectorController::connectToWire(IWireController *wire) {

}
