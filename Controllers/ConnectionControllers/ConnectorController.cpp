//
// Created by Кир on 19.01.2021.
//

#include "ConnectionsController.h"

ConnectorController::ConnectorController(BaseParam, ConnectorParam, RenderWindow* window) : BaseInit, ConnectorInit, RendererInit {
    renderer = ConnectionRender(window,ConnectionRadius);
}

void ConnectorController::checkEvents(sf::Event event) {
    if (isBlocked) return;

}

void ConnectorController::render() {
    renderer.render();
}

void ConnectorController::connectToWire(IWireController *wire) {
    renderer.render();
}
