//
// Created by Кир on 21.01.2021.
//

#ifndef GATEGAME_COMPONENTLISTELEMENT_H
#define GATEGAME_COMPONENTLISTELEMENT_H
#include "ComponentListController.h"
#include "ComponentController.h"

class ComponentListElement : public IController {
private:
    int index;
    bool isBlocked = false;
    bool mouseHover = false;
    bool isDragged = false;
    Vector2f position;
    Vector2f renderPosition;
    IComponentLogic* logic;
    ComponentController* component;
    ComponentListController* list;
    Color color;
public:
    ComponentListElement(IComponentLogic* logic, ComponentListController* list, int index);
    ~ComponentListElement();
    void render() override;
    void checkWindowEvents(Event event) override;
    void block() override { isBlocked = true; }
    void unblock() override { isBlocked = false; }
    void setPosition(float x, float y) override { position = Vector2f(x,y); }
    void setSize(float x, float y) override {  }
    float getSizeX() override { return component->getSizeX(); }
    float getSizeY() override { return component->getSizeY(); }
};

#endif //GATEGAME_COMPONENTLISTELEMENT_H
