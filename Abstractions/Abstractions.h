//
// Created by Кир on 17.01.2021.
//

#ifndef PROJECT_ABSTRACTIONS_H
#define PROJECT_ABSTRACTIONS_H

#include "../Core/Component.h"

#include <SFML/Graphics.hpp>
#define WindowEvent sf::Event event

class ICommand {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class IController {
public:
    virtual void checkWindowEvents(WindowEvent) = 0;
    virtual void render() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
};

class IWireController {
public:
    virtual void checkEvents(WindowEvent, bool ConnectorBlock) = 0;
    virtual void render() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual Wire* getWire() = 0;
    virtual ~IWireController() = default;
};

class IConnectorController {
public:
    virtual void checkEvents(WindowEvent, bool WireBlock) = 0;
    virtual void render() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void connectToWire(IWireController* wire) = 0;
    virtual Connector* getConnector() = 0;
    virtual ~IConnectorController() = default;
};

class IComponentController {
public:
    virtual void checkEvents(WindowEvent,bool WireBlock, bool ConnectorBlock) = 0;
    virtual void render() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual IComponent* getComponent() = 0;
    virtual float getPositionX() = 0;
    virtual float getPositionY() = 0;
    virtual ~IComponentController() = default;
};

class IComponentFieldController : public IController {
public:
    virtual IComponentController* addNewComponent(float x, float y) = 0;
    virtual void removeComponent(IComponentController* controller) = 0;
    virtual void addInput() = 0;
    virtual void removeInput() = 0;
    virtual void addOutput() = 0;
    virtual void removeOutput() = 0;
};


#endif //PROJECT_ABSTRACTIONS_H
