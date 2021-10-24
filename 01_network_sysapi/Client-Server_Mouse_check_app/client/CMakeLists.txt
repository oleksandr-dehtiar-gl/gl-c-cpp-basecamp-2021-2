cmake_minimum_required(VERSION 3.5)

add_executable(client main.cpp
    ../modules/network/socket.h
    ../modules/network/socket.cpp
    ../modules/network/messages.h
    ../modules/network/message.h
    ../modules/sys_api/mousetracker.h
    ../modules/sys_api/mousetracker.cpp
    ../modules/sys_api/mouselocation.cpp
    ../modules/sys_api/mouselocation.h
    ../modules/sys_api/time.h
    ../modules/sys_api/time.cpp
    )

target_include_directories(client PUBLIC ../modules)
if(UNIX AND NOT APPLE)
    target_link_libraries(client "X11")
endif()
