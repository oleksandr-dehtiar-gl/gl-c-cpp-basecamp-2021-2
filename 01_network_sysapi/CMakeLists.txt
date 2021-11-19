cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(Task1  VERSION 1.0  LANGUAGES CXX)

IF(UNIX)
ADD_DEFINITIONS(-U__STRICT_ANSI__)
ENDIF(UNIX)

add_executable(Server server/main.cpp server/timer.cpp tcp/src/TcpClient.cpp tcp/src/TcpServer.cpp )

add_executable(Client client/main.cpp tcp/src/TcpClient.cpp tcp/src/TcpServer.cpp)


IF(WIN32)
target_link_libraries(Server PUBLIC ws2_32)

target_link_libraries(Client PUBLIC ws2_32)
ENDIF(WIN32)