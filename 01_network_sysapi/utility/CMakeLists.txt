add_library(Utility STATIC)

target_include_directories(Utility 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(Utility
	PUBLIC
		transferUtiltiy.hpp
	PRIVATE
		transferUtiltiy.cpp
)

# ===================================
add_library(TimeWorkingApp INTERFACE)

target_include_directories(TimeWorkingApp 
	INTERFACE 
		"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(TimeWorkingApp
	INTERFACE
		appExecutionTimer.hpp
)
