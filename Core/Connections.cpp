//
// Created by Кир on 10.01.2021.
//
#include "Component.h"
#include <algorithm>

// Connector

void Connector::connect(Wire *wire) {
    if (wire != nullptr) {
        wire->connect(&inputValue);
        connectedWire = wire;
        f_isConnected = true;
        wire->DisconnectAllEvent::attachListener(this);
        if (component != nullptr) {
            wire->TransmitEvent::attachListener(component);
        }
        wire->transmitCurrentState();
    }
}

void Connector::disconnect() {
    if (connectedWire != nullptr) {
        connectedWire->disconnect(&inputValue);
        connectedWire->DisconnectAllEvent::detachListener(this);
        if (component != nullptr) {
            connectedWire->TransmitEvent::detachListener(component);
        }
        connectedWire = nullptr;
        f_isConnected = false;
    }
}

void Connector::invokeEvent() {
    connectedWire = nullptr;
}

// Wire

void Wire::disconnectAll() {
    destinations.clear();
    DisconnectAllEvent::notifyListeners();
    DisconnectAllEvent::eraseAllListeners();
    TransmitEvent::eraseAllListeners();
}

void Wire::transmitCurrentState() {
    if (!destinations.empty()) {
        for (auto &destination : destinations) {
            *destination = value;
            TransmitEvent::notifyListeners();
        }
    }
}

// Danger Zone
// Note:
// Use only methods, described above
// Dont use "connect" and "disconnect" methods, when you trying to connect the value
// Use class "Connector" for it

void Wire::connect(bool *variable) {
    if (variable != nullptr && !(find(destinations.begin(), destinations.end(), variable) != destinations.end())) {
        destinations.push_back(variable);
    }
}

void Wire::disconnect(bool *variable) {
    auto iterator = find(destinations.begin(), destinations.end(), variable);
    if (variable != nullptr && iterator != destinations.end()) {
        destinations.erase(iterator);
    }
}