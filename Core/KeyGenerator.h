//
// Created by Кир on 15.01.2021.
//

#ifndef PROJECT_KEYGENERATOR_H
#define PROJECT_KEYGENERATOR_H

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class KeyGenerator {
private:
    vector<int> keys;
    queue<int> deletedKeys;
public:
    int generateKey();

    void deleteKey(int key);
};

#endif //PROJECT_KEYGENERATOR_H
