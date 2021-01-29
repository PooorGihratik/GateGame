//
// Created by Кир on 19.01.2021.
//

#include "Command.h"

AddNewOutput::AddNewOutput(IComponentFieldController *field) : field(field){

}

void AddNewOutput::execute() {
    field->addOutput();
    isExecuted = true;
}

void AddNewOutput::undo() {
    if (isExecuted) field->removeOutput();
}