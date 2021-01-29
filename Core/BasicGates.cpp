//
// Created by Кир on 10.01.2021.
//
#include "ComponentLogic.h"

using namespace std;

bool * NOT::getOutputs(bool* input) {
    bool* output = new bool;
    *output = !(*input);
    return output;
}

bool * AND::getOutputs(bool* input) {
    bool* output = new bool;
    *output = input[0] && input[1];
    return output;
}