
add_library(NetworkAPI STATIC)

target_sources(NetworkAPI
	PUBLIC
		netApi.hpp
)

target_include_directories(NetworkAPI 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

if(WIN32)

	target_sources(NetworkAPI
		PRIVATE
			netApiWin.cpp
	)
	
	if(MINGW)
		target_link_libraries(NetworkAPI
			PRIVATE 
				ws2_32
		)
	endif(MINGW)
	
endif(WIN32)
