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
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    logicelement.h
    logicelement.cpp
    scene.h
    scene.cpp
    graphicselement.h
    graphicselement.cpp
    elementtype.h


    LogicGates/andgate.h
    LogicGates/andgate.cpp
    LogicGates/nandgate.h
    LogicGates/nandgate.cpp
    LogicGates/xorgate.h
    LogicGates/xorgate.cpp
    LogicGates/notgate.h
    LogicGates/notgate.cpp
    LogicGates/norgate.h
    LogicGates/norgate.cpp
    LogicGates/orgate.h
    LogicGates/orgate.cpp

    LogicGatesGraphics/andgategraphicselement.h
    LogicGatesGraphics/andgategraphicselement.cpp
    LogicGatesGraphics/nandgategraphicselement.h
    LogicGatesGraphics/nandgategraphicselement.cpp
    LogicGatesGraphics/norgategraphicselement.h
    LogicGatesGraphics/norgategraphicselement.cpp
    LogicGatesGraphics/notgategraphicselement.h
    LogicGatesGraphics/notgategraphicselement.cpp
    LogicGatesGraphics/orgategraphicselement.h
    LogicGatesGraphics/orgategraphicselement.cpp
    LogicGatesGraphics/xorgategraphicselement.h
    LogicGatesGraphics/xorgategraphicselement.cpp



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
