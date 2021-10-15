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

add_subdirectory(transferBigData/server)
add_subdirectory(transferBigData/client)
