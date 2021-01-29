//
// Created by Кир on 15.01.2021.
//

#ifndef PROJECT_COMPONENTFACTORY_H
#define PROJECT_COMPONENTFACTORY_H

#include "Component.h"

class ComponentFactory {
private:
    int countOfBasicComponents;
    vector<IComponentLogic*> componentLogicList;
    int selectedComponent = 0;
public:
    ComponentFactory();

    void addComponentToList(IComponentLogic* logic);

    void removeComponentFromList();

    void selectComponent(int index);

    int getCountOfComponents() { return countOfBasicComponents; }

    Component *getSelectedComponent();

    vector<IComponentLogic*>::iterator getIterator() { return componentLogicList.begin(); }

    ~ComponentFactory();
};

#endif //PROJECT_COMPONENTFACTORY_H
