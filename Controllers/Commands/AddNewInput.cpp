//
// Created by Кир on 19.01.2021.
//
#include "Command.h"

AddNewInput::AddNewInput(IComponentFieldController *field) : field(field) {

}

void AddNewInput::execute() {
    field->addInput();
    isExecuted = true;
}

void AddNewInput::undo() {
    if (isExecuted) field->removeInput();
}