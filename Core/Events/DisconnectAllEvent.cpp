//
// Created by Кир on 14.01.2021.
//
#include "Event.h"

void DisconnectAllEvent::attachListener(DisconnectAllEventListener *listener) {
    listeners.push_back(listener);
}

void DisconnectAllEvent::detachListener(DisconnectAllEventListener *listener) {
    listeners.remove(listener);
}

void DisconnectAllEvent::eraseAllListeners() {
    listeners.clear();
}

void DisconnectAllEvent::notifyListeners() {
    if (listeners.empty()) return;
    for (auto &listener : listeners) {
        listener->invokeEvent();
    }
}
