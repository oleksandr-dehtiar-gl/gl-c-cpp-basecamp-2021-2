cmake_minimum_required (VERSION 3.8)
project ("MessengerNetworking")

file(GLOB SOURCES src/* src/*/* src/*/*/*)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE::include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)