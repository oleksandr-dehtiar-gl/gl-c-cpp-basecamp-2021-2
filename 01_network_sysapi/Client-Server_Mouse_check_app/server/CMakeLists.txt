cmake_minimum_required(VERSION 3.5)

add_executable(server main.cpp
    ../modules/network/socket.h
    ../modules/network/socket.cpp
    ../modules/network/messages.h
    ../modules/network/message.h
    ../modules/sys_api/mousetracker.h
    ../modules/sys_api/mousetracker.cpp
    ../modules/sys_api/mouselocation.cpp
    ../modules/sys_api/mouselocation.h
    )

target_include_directories(server PUBLIC ../modules)
if(UNIX AND NOT APPLE)
    target_link_libraries(server "X11")
endif()
