//
// Created by Кир on 23.01.2021.
//
#include "Component.h"

#define ConnectorInit connectors(vector<Connector>(logic->getCountOfInputs(),Connector(this)))
#define WireInit wires(vector<Wire>(logic->getCountOfOutputs()))

Component::Component(IComponentLogic *logic) : logic(logic), ConnectorInit, WireInit { }

vector<Connector>::iterator Component::getConnectors(){
    return connectors.begin();
}

vector<Wire>::iterator Component::getWires() {
    return wires.begin();
}

void Component::clearAllConnections() {
    for(auto wire : wires) {
        wire.disconnectAll();
    }
    for(auto connector : connectors) {
        connector.disconnect();
    }
}

void Component::findOutputs() {
    bool* inputs;
    if (!connectors.empty()) {
        inputs = new bool[connectors.size()];
        for (int i=0;i<connectors.size();i++) {
            inputs[i]=connectors[i].getValue();
        }
    }
    else inputs = nullptr;
    bool* outputs = logic->getOutputs(inputs);
    for (int i=0;i<wires.size();i++) {
        wires[i].setValue(outputs[i]);
        wires[i].transmitCurrentState();
    }
    delete[] inputs;
    delete[] outputs;
}

Component* Component::clone() {
    return new Component(logic);
}

void Component::invokeEvent() {
    findOutputs();
}