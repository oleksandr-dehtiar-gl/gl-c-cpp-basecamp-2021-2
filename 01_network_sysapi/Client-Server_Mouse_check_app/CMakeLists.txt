cmake_minimum_required(VERSION 3.5)

project(Client-Server_Mouse_check_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(server)
add_subdirectory(client)

include_directories("modules")

add_subdirectory(modules/network)
add_subdirectory(modules/sys_api)
