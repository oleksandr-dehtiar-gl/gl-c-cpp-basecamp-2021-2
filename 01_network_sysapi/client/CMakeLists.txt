cmake_minimum_required(VERSION 3.15)

project(Client_TransferBigData VERSION 1.0.0
	DESCRIPTION "client application for send data > 100 MB"
)

add_executable(Client 
	client.cpp
	transferDataClient.hpp
	transferDataClient.cpp
)

target_include_directories(Client 
	PRIVATE 
		Network
		Utility
		Headers
		Threadguard
		ThreadSafeQueue
		TimeWorkingApp
)

target_link_libraries(Client
	PRIVATE 
		Network
		Utility
		Headers
		Threadguard
		ThreadSafeQueue
		TimeWorkingApp
)
