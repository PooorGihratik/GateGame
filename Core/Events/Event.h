//
// Created by Кир on 12.01.2021.
//

#ifndef PROJECT_EVENT_H
#define PROJECT_EVENT_H

#include <list>

using namespace std;

class TransmitEventListener {
public:
    virtual void invokeEvent() = 0;
};

class TransmitEvent {
protected:
    list<TransmitEventListener *> listeners;
public:
    void attachListener(TransmitEventListener *listener);

    void detachListener(TransmitEventListener *listener);

    void eraseAllListeners();

    void notifyListeners();
};

class DisconnectAllEventListener {
public:
    virtual void invokeEvent() = 0;
};

class DisconnectAllEvent {
protected:
    list<DisconnectAllEventListener *> listeners;
public:
    void attachListener(DisconnectAllEventListener *listener);

    void detachListener(DisconnectAllEventListener *listener);

    void eraseAllListeners();

    void notifyListeners();
};

#endif //PROJECT_EVENT_H
