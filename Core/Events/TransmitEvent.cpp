//
// Created by Кир on 14.01.2021.
//
#include "Event.h"

void TransmitEvent::attachListener(TransmitEventListener *listener) {
    listeners.push_back(listener);
}

void TransmitEvent::detachListener(TransmitEventListener *listener) {
    listeners.remove(listener);
}

void TransmitEvent::eraseAllListeners() {
    listeners.clear();
}

void TransmitEvent::notifyListeners() {
    if (listeners.empty()) return;
    for (auto &listener : listeners) {
        listener->invokeEvent();
    }
}
