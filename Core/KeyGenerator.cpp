//
// Created by Кир on 15.01.2021.
//
#include "KeyGenerator.h"

int KeyGenerator::generateKey() {
    if (deletedKeys.empty()) {
        keys.push_back(keys.size());
        return keys.size() - 1;
    } else {
        int key = deletedKeys.front();
        deletedKeys.pop();
        keys.push_back(key);
        return key;
    }
}

void KeyGenerator::deleteKey(int key) {
    deletedKeys.push(key);
    auto iter = find(keys.begin(), keys.end(), key);
    if (keys.end() != iter)
        keys.erase(iter);
}