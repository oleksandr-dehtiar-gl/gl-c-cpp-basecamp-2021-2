#cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Network)

add_executable(Client Network_Client/main.cpp)
add_executable(Server Network_Server/main.cpp)