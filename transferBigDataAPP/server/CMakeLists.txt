cmake_minimum_required(VERSION 3.20)

project(Server_TransferBigData VERSION 1.0.0
	DESCRIPTION "server application for recive data > 100 MB"
)

add_executable(server 
	server.cpp
	transferDataServer.cpp
	transferDataServer.hpp
)

target_include_directories(server 
	PUBLIC NetworkAPI
	PUBLIC Utility
)

target_link_libraries(server
	PUBLIC NetworkAPI
	PUBLIC Utility
	PUBLIC Connection
	INTERFACE AppExecutionTimer
	INTERFACE Packet
	INTERFACE Threadguard
	INTERFACE ThreadSafeQueue
)
