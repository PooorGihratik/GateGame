//
// Created by Кир on 10.01.2021.
//
#include "Component.h"

using namespace std;

// NOT

void NOT::invokeEvent() {
    output.transmitToAll(!input.getValue());
}

void NOT::update() {

}

void NOT::clearAllConnections() {
    output.disconnectAll();
    input.disconnect();
}

IComponent *NOT::clone() {
    return new NOT();
}

NOT::~NOT() {
    output.disconnectAll();
}

// AND

void AND::invokeEvent() {
    output.transmitToAll(inputs[0].getValue() && inputs[1].getValue());
}

void AND::update() {

}

void AND::clearAllConnections() {
    output.disconnectAll();
    inputs[0].disconnect();
    inputs[1].disconnect();
}

IComponent *AND::clone() {
    return new AND();
}

AND::~AND() {
    output.disconnectAll();
}