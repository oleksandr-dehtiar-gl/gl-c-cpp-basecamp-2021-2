cmake_minimum_required (VERSION 3.8)
project ("MessengerNetworking")

add_library(${PROJECT_NAME} src/test.cpp src/tcp_server.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE::include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)