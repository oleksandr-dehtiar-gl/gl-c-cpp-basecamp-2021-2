add_library(Headers STATIC)

target_include_directories(Headers 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(Headers
	PUBLIC
		header.hpp
	PRIVATE
		header.cpp
)

target_include_directories(Headers
	PUBLIC
		Network
)

target_link_libraries(Headers
	PUBLIC
		Network
)
