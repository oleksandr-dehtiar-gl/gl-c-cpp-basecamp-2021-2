add_library(Network STATIC)

target_sources(Network
	PUBLIC
		network.hpp
	PRIVATE
		networkDefine.hpp
		guardAddrinfo.hpp
		guardAddrinfo.cpp
		mySocket.hpp
		mySocket.cpp
)

target_include_directories(Network 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

if(WIN32)
	target_sources(Network
		PRIVATE
			networkWin.cpp
	)
endif(WIN32)
