cmake_minimum_required (VERSION 3.8)
project ("MessengerClient")

add_executable (${PROJECT_NAME} MessengerClient.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
            MessengerNetworking

)
target_link_libraries(${PROJECT_NAME}
        PUBLIC
            MessengerNetworking
)
