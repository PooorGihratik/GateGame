//
// Created by Кир on 19.01.2021.
//
#include "Command.h"

RemoveOutput::RemoveOutput(IComponentFieldController *field) : field(field){}

void RemoveOutput::execute() {
    field->removeOutput();
    isExecuted = true;
}

void RemoveOutput::undo() {
    if (isExecuted) {
        // TODO Create undo() function
    }
}