cmake_minimum_required (VERSION 3.8)
project ("MessengerClient")

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("MessengerNetworking")

add_subdirectory("MessengerClient")
add_subdirectory("MessengerServer")
