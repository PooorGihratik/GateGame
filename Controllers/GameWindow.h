//
// Created by Кир on 17.01.2021.
//

#ifndef PROJECT_GAMEWINDOW_H
#define PROJECT_GAMEWINDOW_H
#include <list>
#include <SFML/Graphics.hpp>
#include "Abstractions/Abstractions.h"
#include "Core/ComponentNetwork.h"

using namespace std;
using namespace sf;

class GameWindow {
private:
    RenderWindow* window;
    list<IController*> controllerList;
    IController* focusedController = nullptr;
    ComponentNetwork* network;
    ICommand* command;
public:
    void init();
    void updateLoop();
    void render();
    void checkWindowEvents(Event event);
    void gotFocusEvent(IController* controller);
    void lostFocusEvent();
    void setCommand(ICommand* command) { this->command = command; };
    RenderWindow* getWindow() { return window; }
};

#endif //PROJECT_GAMEWINDOW_H
