add_library(Utility STATIC)

target_include_directories(Utility 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(Utility
	PUBLIC
		transferUtility.hpp
		transferUtility.cpp
)
