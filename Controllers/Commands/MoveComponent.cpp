//
// Created by Кир on 18.01.2021.
//
#include "Command.h"


void MoveComponent::execute() {
    component->setPosition(x,y);
}

void MoveComponent::undo() {
    component->setPosition(bufferX,bufferY);
}