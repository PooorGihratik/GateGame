//
// Created by Кир on 10.01.2021.
//

#ifndef PROJECT_COMPONENT_H
#define PROJECT_COMPONENT_H

#include <string>
#include <vector>
#include <array>
#include "Events/Event.h"
#include "ComponentLogic.h"
#include <iostream>

using namespace std;

class Wire : public DisconnectAllEvent, public TransmitEvent {
private:
    bool value = false;
    vector<bool *> destinations;
public:
    bool getValue() const { return value; }

    void setValue(bool val) { value = val; }

    void connect(bool *destination);

    void disconnect(bool *destination);

    void disconnectAll();

    void transmitCurrentState();
};

class Connector : public DisconnectAllEventListener {
private:
    Wire *connectedWire = nullptr;
    bool inputValue = false;
    bool f_isConnected = false;
    TransmitEventListener *component = nullptr;
public:
    Connector() = default;
    explicit Connector(TransmitEventListener *component) : component(component) {}
    void connect(Wire *wire);
    void invokeEvent() override;
    bool getValue() const { return inputValue; }
    bool isConnected() const { return f_isConnected; }
    void disconnect();
};

class Component : public TransmitEventListener {
private:
    IComponentLogic* logic;
    vector<Connector> connectors;
    vector<Wire> wires;
public:
    Component(IComponentLogic* logic);

    vector<Connector>::iterator getConnectors();
    vector<Wire>::iterator getWires();
    int getCountOfOutputs() { return logic->getCountOfOutputs(); }
    int getCountOfInputs() { return logic->getCountOfInputs(); }
    string getName() { return logic->getName(); }
    void clearAllConnections();
    void findOutputs();
    Component *clone();
    void invokeEvent() override;
};
#endif //PROJECT_COMPONENT_H
