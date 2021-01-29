//
// Created by Кир on 11.01.2021.
//
#include "ComponentNetwork.h"
#include <algorithm>

Component* ComponentNetwork::addComponent() {
    //components.insert({factory.getSelectedComponent(), generator.generateKey()});
    Component* component = factory.getSelectedComponent();
    components.push_back(component);
    return component;
}

void ComponentNetwork::removeComponent(Component *component) {
    auto iter = find(components.begin(),components.end(),component);
    //generator.deleteKey(iter->second);
    delete *iter;
    components.erase(iter);
}

void ComponentNetwork::update() {
    for (auto &input:inputs) {
        input.transmitCurrentState();
    }
}

Connector *ComponentNetwork::addConnector() {
    outputs.emplace_back(this);
    return &outputs.back();
}

void ComponentNetwork::removeConnector() {
    outputs.back().disconnect();
    outputs.pop_back();
}

Wire *ComponentNetwork::addWire() {
    inputs.emplace_back();
    return &inputs.back();
}

void ComponentNetwork::removeWire() {
    inputs.back().disconnectAll();
    inputs.pop_back();
}

void ComponentNetwork::invokeEvent() {

}

bool * ComponentNetwork::getOutputs(bool* input) {
    auto iterIn = inputs.begin();
    for (int i=0;i<inputs.size();i++) {
        iterIn->setValue(input[i]);
        iterIn->transmitCurrentState();
    }
    update();
    bool* output = new bool[outputs.size()];
    auto iterOut = outputs.begin();
    for (int i=0;i<outputs.size();i++) {
        output[i] = iterOut++->getValue();
    }
    return output;
}