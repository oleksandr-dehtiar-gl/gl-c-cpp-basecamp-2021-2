cmake_minimum_required (VERSION 3.8)
project ("MessengerServer")
add_executable (${PROJECT_NAME} MessengerServer.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
            MessengerNetworking

)
target_link_libraries(${PROJECT_NAME}
        PUBLIC
            MessengerNetworking
            ws2_32
)
