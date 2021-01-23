//
// Created by Кир on 19.01.2021.
//
#include "Command.h"

AddInput::AddInput(IComponentFieldController *field) : field(field) {

}

void AddInput::execute() {
    field->addInput();
    isExecuted = true;
}

void AddInput::undo() {
    if (isExecuted) field->removeInput();
}