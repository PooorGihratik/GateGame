//
// Created by Кир on 19.01.2021.
//

#include "Command.h"

#define ConstructorParam IComponentFieldController *controller, float x, float y
#define InitList controller(controller), x(x), y(y)

AddComponentToField::AddComponentToField(ConstructorParam) : InitList {
}

void AddComponentToField::execute() {
    component = controller->addNewComponent(x,y);
    isExecuted = true;
}

void AddComponentToField::undo() {
    if (isExecuted) controller->removeComponent(component);
}