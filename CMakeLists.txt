cmake_minimum_required(VERSION 3.16)
project(GateGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(GateGame main.cpp Core/Component.h Core/BasicGates.cpp Core/Connections.cpp Core/ComponentNetwork.h Core/ComponentNetwork.cpp Core/Events/Event.h Core/CompositeComponent.h Core/CompositeComponent.cpp Core/Events/TransmitEvent.cpp Core/Events/DisconnectAllEvent.cpp Core/ComponentFactory.h Core/ComponentFactory.cpp Core/KeyGenerator.h Core/KeyGenerator.cpp GameWindow.cpp GameWindow.h Abstractions/Abstractions.h Controllers/ComponentFieldController.cpp Controllers/ComponentFieldController.h Controllers/ComponentController.cpp Controllers/ComponentController.h Controllers/ConnectionControllers/ConnectionsController.h Controllers/Commands/Command.h Controllers/Commands/MoveComponent.cpp Controllers/ConnectionControllers/FieldConnectorController.cpp Controllers/ConnectionControllers/FieldWireController.cpp Controllers/ConnectionControllers/ComponentWireController.cpp Controllers/ConnectionControllers/ComponentConnectorController.cpp Controllers/Commands/AddComponentToField.cpp Controllers/Commands/ConnectCommand.cpp)
link_directories("D:/CLionProjects/Libs/SFML-2.5.1 MinGw")
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(GateGame ${SFML_LIBRARIES})
endif ()