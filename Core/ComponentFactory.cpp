//
// Created by Кир on 15.01.2021.
//
#include "ComponentFactory.h"

ComponentFactory::ComponentFactory() {
    componentLogicList.push_back(new AND());
    componentLogicList.push_back(new NOT());
    countOfBasicComponents = componentLogicList.size();
}

void ComponentFactory::addComponentToList(IComponentLogic* logic) {
    if (logic != nullptr) componentLogicList.push_back(logic);
}

void ComponentFactory::removeComponentFromList() {
    if (selectedComponent < countOfBasicComponents) return;
    auto iterator = componentLogicList.begin() + selectedComponent;
    delete *iterator;
    componentLogicList.erase(iterator);
}

Component *ComponentFactory::getSelectedComponent() {
    return new Component(componentLogicList[selectedComponent]);
}

void ComponentFactory::selectComponent(int index) {
    if (index >= 0 && index < componentLogicList.size()) {
        selectedComponent = index;
    }
}

ComponentFactory::~ComponentFactory() {
    for (auto &component:componentLogicList) {
        delete component;
    }
}

