cmake_minimum_required(VERSION 3.5)

add_library(Network STATIC
    socket.h
    socket.cpp
    messages.h
    message.h
    )
