cmake_minimum_required(VERSION 3.20)

project(Server_TransferBigData VERSION 1.0.0
	DESCRIPTION "server application for recive data > 100 MB"
	LANGUAGES CXX
)

add_executable(server 
	Server_TransferBigData.cpp
)

target_include_directories(server 
	PUBLIC NetworkAPI
)

target_link_libraries(server
	PUBLIC NetworkAPI
)
