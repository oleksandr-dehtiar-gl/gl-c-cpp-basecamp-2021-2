set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_minimum_required(VERSION 3.20)

project(TransferBigData VERSION 1.0.0
	DESCRIPTION "client/server application for send data > 100 MB"
	LANGUAGES CXX
)

if(NOT WIN32 AND NOT LINUX)
	message(FATAL_ERROR "APPS PORTABLE ONLY ON WINDOWS OR LINUX")
endif(NOT WIN32 AND NOT LINUX)

# Project build rulls
# ===================
add_subdirectory(01_network_sysapi)

add_subdirectory(04_utility)
add_subdirectory(02_oop/transferBigData)

add_subdirectory(transferBigDataAPP/server)
add_subdirectory(transferBigDataAPP/client)
