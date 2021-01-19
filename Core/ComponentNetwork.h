//
// Created by Кир on 11.01.2021.
//

#ifndef PROJECT_CUSTOMCOMPONENTS_H
#define PROJECT_CUSTOMCOMPONENTS_H

#include "Component.h"
#include "ComponentFactory.h"
#include "KeyGenerator.h"
#include <map>
#include <list>

class ComponentNetwork : public TransmitEventListener {
private:
    list<Wire> inputs;
    list<Connector> outputs;
    map<IComponent *, int> components;
    ComponentFactory factory;
    KeyGenerator generator;
public:
    IComponent *addComponent();

    void removeComponent(IComponent *component);

    Wire *addWire();

    void removeWire();

    Connector *addConnector();

    void removeConnector();

    list<Wire> *getWires() { return &inputs; }

    list<Connector> *getConnectors() { return &outputs; }

    ComponentFactory *getFactory() { return &factory; }


    void invokeEvent() override;

    void update();
};

#endif //PROJECT_CUSTOMCOMPONENTS_H
