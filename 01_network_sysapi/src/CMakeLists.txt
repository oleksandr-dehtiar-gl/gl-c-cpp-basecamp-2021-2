cmake_minimum_required(VERSION 3.1)
project (gl_network VERSION 1.0)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(gl_server gl_server/Source.cpp
                gl_networking/Includes.h
                gl_networking/IPEndPoint.h  gl_networking/IPEndPoint.cpp
                gl_networking/IPVersion.h
                gl_networking/Network.h     gl_networking/Network.cpp
                gl_networking/Packet.h      gl_networking/Packet.cpp
                gl_networking/PacketType.h
                gl_networking/Result.h
                gl_networking/MySocket.h      gl_networking/MySocket.cpp
                gl_networking/SocketHandle.h
                gl_networking/SocketOption.h)

add_executable(gl_client gl_client/Source.cpp
                gl_sysapi/ProcessManager.h       gl_sysapi/ProcessManager.cpp      
                gl_networking/Includes.h
                gl_networking/IPEndPoint.h  gl_networking/IPEndPoint.cpp
                gl_networking/IPVersion.h
                gl_networking/Network.h     gl_networking/Network.cpp
                gl_networking/Packet.h      gl_networking/Packet.cpp
                gl_networking/PacketType.h
                gl_networking/Result.h
                gl_networking/MySocket.h      gl_networking/MySocket.cpp
                gl_networking/SocketHandle.h
                gl_networking/SocketOption.h)
set_target_properties(gl_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set_target_properties(gl_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
