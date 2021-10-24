add_library(Packet INTERFACE)

target_include_directories(Packet 
	INTERFACE 
		"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(Packet
	INTERFACE
		packet.hpp
)

target_link_libraries(Packet
	INTERFACE
		NetworkAPI
)


# ==================================

add_library(Threadguard INTERFACE)

target_include_directories(Threadguard 
	INTERFACE 
		"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(Threadguard
	INTERFACE
		threadGuard.hpp
)

# ==================================

add_library(AppExecutionTimer INTERFACE)

target_include_directories(AppExecutionTimer 
	INTERFACE 
		"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(AppExecutionTimer
	INTERFACE
		appExecutionTimer.hpp
)

# ==================================

add_library(ThreadSafeQueue INTERFACE)

target_include_directories(ThreadSafeQueue 
	INTERFACE 
		"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(ThreadSafeQueue
	INTERFACE
		threadSafeQueue.hpp
)

# ==================================

add_library(Connection STATIC)

target_sources(Connection
	PUBLIC
		connection.hpp
		connection.cpp
)

target_include_directories(Connection 
	PUBLIC 
		"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(Connection
	PUBLIC
		NetworkAPI
)

# ==================================
