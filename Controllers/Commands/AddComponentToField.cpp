//
// Created by Кир on 19.01.2021.
//

#include "Command.h"

#define ConstructorParam ComponentFieldController *controller, float x, float y
#define InitList controller(controller), x(x), y(y)

AddComponentToField::AddComponentToField(ConstructorParam) : InitList {
}

void AddComponentToField::execute() {
    controller->addNewComponent(x,y);
}

void AddComponentToField::undo() {
    controller->removeComponent()
}