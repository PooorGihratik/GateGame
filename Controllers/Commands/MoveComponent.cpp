//
// Created by Кир on 18.01.2021.
//
#include "Command.h"


void MoveComponent::execute() {
    component->setPosition(x,y);
    isExecuted = true;
}

void MoveComponent::undo() {
    if (isExecuted) component->setPosition(bufferX,bufferY);
}