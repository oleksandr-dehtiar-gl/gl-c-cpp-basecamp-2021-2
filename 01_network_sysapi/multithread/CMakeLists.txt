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

add_library(ThreadSafeQueue INTERFACE)

target_include_directories(ThreadSafeQueue 
	INTERFACE 
		"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(ThreadSafeQueue
	INTERFACE
		threadSafeQueue.hpp
)
