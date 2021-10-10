cmake_minimum_required(VERSION 3.20)

project(Client_TransferBigData VERSION 1.0.0
	DESCRIPTION "client application for send data > 100 MB"
	LANGUAGES CXX
)

add_executable(client
	Client_TransferBigData.cpp
)

target_include_directories(client 
	PUBLIC NetworkAPI
)

target_link_libraries(client
	PUBLIC NetworkAPI
)