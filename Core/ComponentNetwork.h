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

class ComponentNetwork : public TransmitEventListener, public IComponentLogic {
private:
    list<Wire> inputs;
    list<Connector> outputs;
    list<Component*> components;
    ComponentFactory factory;
    KeyGenerator generator;
    string name = "new network...";
public:
    Component* addComponent();

    void removeComponent(Component *component);

    Wire *addWire();

    void removeWire();

    Connector *addConnector();

    void removeConnector();

    ComponentFactory *getFactory() { return &factory; }

    void invokeEvent() override;

    void update();

    bool* getOutputs(bool* input) override;
    int getCountOfInputs() override { return inputs.size(); }
    int getCountOfOutputs() override { return outputs.size(); }
    string getName() override { return name; }
};

#endif //PROJECT_CUSTOMCOMPONENTS_H
