//
// Created by Кир on 15.01.2021.
//
#include "ComponentFactory.h"

ComponentFactory::ComponentFactory() {
    components.push_back(new AND());
    components.push_back(new NOT());
    countOfBasicComponents = components.size();
}

void ComponentFactory::addComponentToList(IComponent *component) {

}

void ComponentFactory::removeComponentFromList() {
    if (selectedComponent < countOfBasicComponents) return;
    auto iterator = components.begin() + selectedComponent;
    components.erase(iterator);
}

IComponent *ComponentFactory::getSelectedComponent() {
    return components[selectedComponent]->clone();
}

void ComponentFactory::selectComponent(int index) {
    if (index > 0 && index <= components.size()) {
        selectedComponent = index - 1;
    }
}

ComponentFactory::~ComponentFactory() {
    for (auto &component:components) {
        delete component;
    }
}

IComponent *ComponentFactory::getComponentByName(const string &name) {
    for (auto &component:components) {
        if (component->getName() == name) return component->clone();
    }
}

