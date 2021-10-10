cmake_minimum_required(VERSION 3.20)

project(TransferBigData VERSION 1.0.0
	DESCRIPTION "client/server application for send data > 100 MB"
	LANGUAGES CXX
)


# DEFINE platform dependent variables 
# ===================================
if(WIN32)
	set(PLATFORM "WIN32_API")
	if(MSVC)
		set(COMPILER "MSVC")
	else()
		if(MINGW)
			set(COMPILER "MINGW")
		else()
			message(FATAL_ERROR "USE MINGW OR MSVC TOOLS SET")
		endif(MINGW)
	endif(MSVC)
endif(WIN32)

if(UNIX)
	set(PLATFORM "UNIX_API")
	set(COMPILER "GCC")
endif(UNIX)

if(NOT WIN32 AND NOT UNIX)
	message(FATAL_ERROR "APPS PORTABLE ONLY ON WINDOWS OR LINUX")
endif(NOT WIN32 AND NOT UNIX)

configure_file(PlatformConfig.hpp.in PlatformConfig.hpp)

# Project build rulls
# ===================
add_subdirectory(01_network_sysapi)

add_subdirectory(transferBigData/server)
add_subdirectory(transferBigData/client)
