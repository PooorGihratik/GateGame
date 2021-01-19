//
// Created by Кир on 15.01.2021.
//

#ifndef PROJECT_COMPONENTFACTORY_H
#define PROJECT_COMPONENTFACTORY_H

#include "Component.h"

class ComponentFactory {
private:
    int countOfBasicComponents;
    vector<IComponent *> components;
    int selectedComponent = 0;
public:
    ComponentFactory();

    void addComponentToList(IComponent *component);

    void removeComponentFromList();

    void selectComponent(int index);

    IComponent *getSelectedComponent();

    IComponent *getComponentByName(const string &name);

    ~ComponentFactory();
};

#endif //PROJECT_COMPONENTFACTORY_H
