cmake_minimum_required(VERSION 3.20)

project(Client_TransferBigData VERSION 1.0.0
	DESCRIPTION "client application for send data > 100 MB"
)

add_executable(client
	client.cpp
	transferDataClient.hpp
	transferDataClient.cpp
)

target_link_libraries(client
	PUBLIC NetworkAPI
	PUBLIC Utility
	PUBLIC Connection
	INTERFACE AppExecutionTimer
	INTERFACE Packet
	INTERFACE Threadguard
	INTERFACE ThreadSafeQueue
)
