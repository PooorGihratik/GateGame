//
// Created by Кир on 19.01.2021.
//
#include "Command.h"

void ConnectCommand::execute() {
    connector->connectToWire(wire);
    isExecuted = true;
}

void ConnectCommand::undo() {
    if (isExecuted) {
        // TODO Create undo() function
    }
}