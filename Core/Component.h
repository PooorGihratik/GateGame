//
// Created by Кир on 10.01.2021.
//

#ifndef PROJECT_COMPONENT_H
#define PROJECT_COMPONENT_H

#include <string>
#include <vector>
#include "Events/Event.h"

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

    void transmitToAll(bool value);

    void transmitCurrentState();
};

class Connector : public DisconnectAllEventListener {
private:
    Wire *connectedWire = nullptr;
    bool inputValue = false;
    bool f_isConnected = false;
    TransmitEventListener *component;
public:
    explicit Connector(TransmitEventListener *component) : component(component) {}

    void connect(Wire *wire);

    void invokeEvent() override;

    bool getValue() const { return inputValue; }

    bool isConnected() const { return f_isConnected; }

    void disconnect();
};

class IComponent : public TransmitEventListener {
public:
    virtual ~IComponent() = default;

    virtual Connector *getConnectors() = 0;

    virtual Wire *getWires() = 0;

    virtual int getCountOfOutputs() = 0;

    virtual int getCountOfInputs() = 0;

    virtual string getName() = 0;

    virtual void update() = 0;

    virtual void clearAllConnections() = 0;

    virtual IComponent *clone() = 0;
};

class AND final : public IComponent {
private:
    const string name = "AND";
    const int countOfInputs = 2;
    const int countOfOutputs = 1;
    Connector inputs[2];
    Wire output;
public:
    AND() : inputs{Connector(this), Connector(this)} {};

    ~AND() override;

    string getName() override { return name; }

    Wire *getWires() override { return &output; }

    Connector *getConnectors() override { return inputs; }

    int getCountOfInputs() override { return countOfInputs; }

    int getCountOfOutputs() override { return countOfOutputs; }

    void update() override;

    void clearAllConnections() override;

    void invokeEvent() override;

    IComponent *clone() override;
};

class NOT final : public IComponent {
private:
    const string name = "NOT";
    const int countOfInputs = 1;
    const int countOfOutputs = 1;
    Connector input;
    Wire output;
public:
    NOT() : input(Connector(this)) {};

    ~NOT() override;

    string getName() override { return name; }

    int getCountOfInputs() override { return countOfInputs; }

    int getCountOfOutputs() override { return countOfOutputs; }

    Wire *getWires() override { return &output; }

    Connector *getConnectors() override { return &input; }

    void update() override;

    void clearAllConnections() override;

    void invokeEvent() override;

    IComponent *clone() override;
};

#endif //PROJECT_COMPONENT_H
