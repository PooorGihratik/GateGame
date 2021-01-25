//
// Created by Кир on 19.01.2021.
//
#include "Command.h"

#define ConstructorParams IComponentFieldController *controller, IComponentController* component
#define InitList controller(controller), component(component)

RemoveComponentFromField::RemoveComponentFromField(ConstructorParams) : InitList {

}

void RemoveComponentFromField::execute() {
    controller->removeComponent(component);
    isExecuted = true;
}

void RemoveComponentFromField::undo() {
    if (isExecuted) {
        // TODO Using snapshot pattern
        //  Create undo function
    }
}