//
// Created by Кир on 23.01.2021.
//

#ifndef GATEGAME_COMPONENTLOGIC_H
#define GATEGAME_COMPONENTLOGIC_H

#include <string>

using namespace std;

class IComponentLogic {
public:
    virtual int getCountOfOutputs() = 0;

    virtual int getCountOfInputs() = 0;

    virtual string getName() = 0;

    virtual bool* getOutputs(bool* input) = 0;
    virtual ~IComponentLogic() = default;
};

class AND final : public IComponentLogic {
private:
    const string name = "AND";
    const int countOfInputs = 2;
    const int countOfOutputs = 1;
public:
    int getCountOfOutputs() override { return countOfOutputs; }
    int getCountOfInputs() override { return countOfInputs; }
    string getName() override { return name; }
    bool* getOutputs(bool* input) override;
};

class NOT final : public IComponentLogic {
private:
    const string name = "NOT";
    const int countOfInputs = 1;
    const int countOfOutputs = 1;
public:
    int getCountOfOutputs() override { return countOfOutputs; }
    int getCountOfInputs() override { return countOfInputs; }
    string getName() override { return name; }
    bool* getOutputs(bool* input) override;
};

#endif //GATEGAME_COMPONENTLOGIC_H
