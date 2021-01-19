//
// Created by Кир on 17.01.2021.
//

#ifndef PROJECT_CONNECTIONSCONTROLLER_H
#define PROJECT_CONNECTIONSCONTROLLER_H

#include "../../Abstractions/Abstractions.h"
#include "../ComponentController.h"

#define ComponentParam ComponentController *component
#define WireParam Wire *wire
#define ConnectorParam Connector *connector
#define FieldParam ComponentFieldController* field

#define ComponentInit component(component)
#define WireInit wire(wire)
#define ConnectorInit connector(connector)
#define FieldInit field(field)

class ComponentWireController : public IWireController {
private:
    ComponentController* component;
    Wire* wire;
    float radius = ConnectionRadius;
    Vector2f position;
    bool isBlocked = false;
public:
    ComponentWireController(ComponentController* component,Wire* wire);
    void checkEvents(sf::Event event, bool ConnectorBlock) override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }
    void setPosition(float x, float y) override { position = Vector2f(x,y); }
    void render() override;
    Wire* getWire() override { return wire; }
};

class FieldWireController : public IWireController {
private:
    ComponentFieldController* field;
    Wire* wire;
    float radius = ConnectionRadius;
    Vector2f position;
    bool isBlocked = false;
public:
    FieldWireController(ComponentFieldController* field, Wire* wire);
    void checkEvents(sf::Event event, bool ConnectorBlock) override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }
    void setPosition(float x, float y) override { position = Vector2f(x,y); }
    void render() override;
    Wire* getWire() override { return wire; }
};

class ComponentConnectorController : public IConnectorController {
private:
    ComponentController* component;
    Connector* connector;
    float radius = ConnectionRadius;
    Vector2f position;
    bool isBlocked = false;
public:
    ComponentConnectorController(ComponentController* component,Connector* connector);
    void checkEvents(sf::Event event, bool WireBlock) override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }
    void setPosition(float x, float y) override { position = Vector2f(x,y); }
    void render() override;
    Connector* getConnector() override { return connector; }

    void connectToWire(IWireController *wire) override;
};

class FieldConnectorController : public IConnectorController {
private:
    ComponentFieldController* field;
    Connector* connector;
    float radius = ConnectionRadius;
    Vector2f position;
    bool isBlocked = false;
public:
    FieldConnectorController(ComponentFieldController* field, Connector* connector);
    void checkEvents(sf::Event event, bool WireBlock) override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }
    void setPosition(float x, float y) override { position = Vector2f(x,y); }
    void render() override;
    Connector* getConnector() override { return connector; }

    void connectToWire(IWireController *wire) override;
};

#endif //PROJECT_CONNECTIONSCONTROLLER_H
