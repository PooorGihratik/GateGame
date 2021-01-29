//
// Created by Кир on 19.01.2021.
//
#include "Command.h"

RemoveInput::RemoveInput(IComponentFieldController *field) : field(field){

}

void RemoveInput::execute() {
    field->removeInput();
    isExecuted = true;
}

void RemoveInput::undo() {
    if (isExecuted) {
        // TODO create undo() function
    }
}