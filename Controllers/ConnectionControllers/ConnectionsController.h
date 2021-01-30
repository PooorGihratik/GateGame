//
// Created by Кир on 17.01.2021.
//

#ifndef PROJECT_CONNECTIONSCONTROLLER_H
#define PROJECT_CONNECTIONSCONTROLLER_H

#include "../Abstractions/Abstractions.h"
#include "../ComponentController.h"
#include "ConnectionRender.h"

#define BaseParam IConnectionBase* base
#define WireParam Wire *wire
#define ConnectorParam Connector *connector

#define BaseInit base(base)
#define WireInit wire(wire)
#define ConnectorInit connector(connector)
#define RendererInit renderer(ConnectionRender(window,ConnectionRadius))

class WireController : public IWireController {
private:
    IConnectionBase* base;
    Wire* wire;
    ConnectionRender renderer;
    bool mouseHover = false;
    bool isBlocked = false;

    CircleShape shape;
public:
    WireController(IConnectionBase* base, Wire* wire, RenderWindow* window);
    void checkEvents(sf::Event event) override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }
    void setPosition(float x, float y) override { renderer.setPosition(Vector2f(x,y)); }
    void setRelativePosition(float x, float y) override { renderer.setRelativePosition(Vector2f(x,y)); }
    void render() override;
    Wire* getWire() override { return wire; }
};

class ConnectorController : public IConnectorController {
private:
    IConnectionBase* base;
    Connector* connector;
    ConnectionRender renderer;
    bool isBlocked = false;
    bool mouseHover = false;
    CircleShape shape;
public:
    ConnectorController(IConnectionBase* base, Connector* connector, RenderWindow* window);
    void checkEvents(sf::Event event) override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }
    void setPosition(float x, float y) override { renderer.setPosition(Vector2f(x,y)); }
    void setRelativePosition(float x, float y) override { renderer.setRelativePosition(Vector2f(x,y)); }
    void render() override;
    Connector* getConnector() override { return connector; }

    void connectToWire(IWireController *wire) override;
};

class LineController {

};

#endif //PROJECT_CONNECTIONSCONTROLLER_H
