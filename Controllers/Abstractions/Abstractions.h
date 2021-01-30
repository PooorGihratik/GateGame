//
// Created by Кир on 17.01.2021.
//

#ifndef PROJECT_ABSTRACTIONS_H
#define PROJECT_ABSTRACTIONS_H

#include "../../Core/Component.h"

#include <SFML/Graphics.hpp>
#define WindowEvent sf::Event event

class ICommand {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand() = default;
};

class IController {
public:
    virtual void checkWindowEvents(WindowEvent) = 0;
    virtual void render() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setSize(float x, float y) = 0;
    virtual float getSizeX() = 0;
    virtual float getSizeY() = 0;
};

class IWireController {
public:
    virtual void checkEvents(WindowEvent) = 0;
    virtual void render() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual Wire* getWire() = 0;
    virtual void setRelativePosition(float x, float y) = 0;
    virtual ~IWireController() = default;
};

class IConnectorController {
public:
    virtual void checkEvents(WindowEvent) = 0;
    virtual void render() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void connectToWire(IWireController* wire) = 0;
    virtual Connector* getConnector() = 0;
    virtual void setRelativePosition(float x, float y) = 0;
    virtual ~IConnectorController() = default;
};

class IComponentController {
public:
    virtual void checkEvents(WindowEvent) = 0;
    virtual void render() = 0;
    virtual void block() = 0;
    virtual void unblockAll() = 0;
    virtual void blockWires() = 0;
    virtual void blockConnectors() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual Component* getComponent() = 0;
    virtual void setComponent(Component* component) = 0;
    virtual float getSizeX() = 0;
    virtual float getSizeY() = 0;
    virtual float getPositionX() = 0;
    virtual float getPositionY() = 0;
    virtual ~IComponentController() = default;
};

class IComponentFieldController {
public:
    virtual IComponentController* addNewComponent(IComponentController* controller,float x, float y) = 0;
    virtual void removeComponent(IComponentController* controller) = 0;
    virtual void addInput() = 0;
    virtual void removeInput() = 0;
    virtual void addOutput() = 0;
    virtual void removeOutput() = 0;
};

class IConnectionBase {
public:
    virtual void wireFocusEvent(IWireController* wire) = 0;
    virtual void connectorFocusEvent(IConnectorController* connector) = 0;
};


#endif //PROJECT_ABSTRACTIONS_H
