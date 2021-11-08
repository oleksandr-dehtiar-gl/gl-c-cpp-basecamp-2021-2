set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_minimum_required(VERSION 3.15)

project(TransferBigData VERSION 1.0.0
	DESCRIPTION "client/server application for send data > 100 MB"
	LANGUAGES CXX
)

if(NOT WIN32 AND NOT LINUX)
	message(FATAL_ERROR "APPS PORTABLE ONLY ON WINDOWS OR LINUX")
endif(NOT WIN32 AND NOT LINUX)

# Project build rulls
# ===================
add_subdirectory(network)
add_subdirectory(utility)
add_subdirectory(headers)
add_subdirectory(multithread)

add_subdirectory(server)
add_subdirectory(client)
