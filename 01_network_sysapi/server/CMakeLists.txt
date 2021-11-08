cmake_minimum_required(VERSION 3.15)

project(Server_TransferBigData VERSION 1.0.0
	DESCRIPTION "server application for recive data > 100 MB"
)

add_executable(Server 
	server.cpp
	transferDataServer.hpp
	transferDataServer.cpp
)

target_include_directories(Server 
	PRIVATE 
		Network
		Utility
		Headers
		Threadguard
		ThreadSafeQueue
)

target_link_libraries(Server
	PRIVATE
		Network
		Utility
		Headers
		Threadguard
		ThreadSafeQueue
)
