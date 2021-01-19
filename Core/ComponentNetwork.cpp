//
// Created by Кир on 11.01.2021.
//
#include "ComponentNetwork.h"

IComponent *ComponentNetwork::addComponent() {
    components.insert({factory.getSelectedComponent(), generator.generateKey()});
    return factory.getSelectedComponent();
}

void ComponentNetwork::removeComponent(IComponent *component) {
    auto iter = components.find(component);
    generator.deleteKey(iter->second);
    delete iter->first;
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