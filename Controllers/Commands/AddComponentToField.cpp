//
// Created by Кир on 19.01.2021.
//

#include "Command.h"

#define ConstructorParam IComponentFieldController *field, IComponentController* component, float x, float y
#define InitList field(field), component(component) , x(x), y(y)

AddComponentToField::AddComponentToField(ConstructorParam) : InitList {

}



void AddComponentToField::execute() {
    component = field->addNewComponent(component,x,y);
    isExecuted = true;
}

void AddComponentToField::undo() {
    if (isExecuted) field->removeComponent(component);
}