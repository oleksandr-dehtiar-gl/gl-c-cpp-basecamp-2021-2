cmake_minimum_required(VERSION 3.5)

project(gl_oop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


set(PROJECT_SOURCES
    gl_oop/main.cpp
    gl_oop/mainwindow.cpp
    gl_oop/mainwindow.h
    gl_oop/mainwindow.ui
    gl_oop/logicelement.h
    gl_oop/logicelement.cpp
    gl_oop/scene.h
    gl_oop/scene.cpp
    gl_oop/graphicselement.h
    gl_oop/graphicselement.cpp
    gl_oop/elementtype.h
    gl_oop/workspace.h
    gl_oop/workspace.cpp



    gl_oop/LogicGates/andgate.h
    gl_oop/LogicGates/andgate.cpp
    gl_oop/LogicGates/nandgate.h
    gl_oop/LogicGates/nandgate.cpp
    gl_oop/LogicGates/xorgate.h
    gl_oop/LogicGates/xorgate.cpp
    gl_oop/LogicGates/notgate.h
    gl_oop/LogicGates/notgate.cpp
    gl_oop/LogicGates/norgate.h
    gl_oop/LogicGates/norgate.cpp
    gl_oop/LogicGates/orgate.h
    gl_oop/LogicGates/orgate.cpp
    gl_oop/LogicGates/logicinput.h
    gl_oop/LogicGates/logicinput.cpp

    gl_oop/LogicGatesGraphics/andgategraphicselement.h
    gl_oop/LogicGatesGraphics/andgategraphicselement.cpp
    gl_oop/LogicGatesGraphics/nandgategraphicselement.h
    gl_oop/LogicGatesGraphics/nandgategraphicselement.cpp
    gl_oop/LogicGatesGraphics/norgategraphicselement.h
    gl_oop/LogicGatesGraphics/norgategraphicselement.cpp
    gl_oop/LogicGatesGraphics/notgategraphicselement.h
    gl_oop/LogicGatesGraphics/notgategraphicselement.cpp
    gl_oop/LogicGatesGraphics/orgategraphicselement.h
    gl_oop/LogicGatesGraphics/orgategraphicselement.cpp
    gl_oop/LogicGatesGraphics/xorgategraphicselement.h
    gl_oop/LogicGatesGraphics/xorgategraphicselement.cpp
    gl_oop/LogicGatesGraphics/port.h
    gl_oop/LogicGatesGraphics/port.cpp
    gl_oop/LogicGatesGraphics/connection.h
    gl_oop/LogicGatesGraphics/connection.cpp
    gl_oop/LogicGatesGraphics/vccgraphicselement.h
    gl_oop/LogicGatesGraphics/vccgraphicselement.cpp
    gl_oop/LogicGatesGraphics/gndgraphicselement.h
    gl_oop/LogicGatesGraphics/gndgraphicselement.cpp



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gl_oop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET gl_oop APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(gl_oop SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(gl_oop
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(gl_oop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(gl_oop PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gl_oop)
endif()
