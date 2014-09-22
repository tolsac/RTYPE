cmake_minimum_required(VERSION 2.8)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/includes/*)
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	      ${CMAKE_CURRENT_SOURCE_DIR}/../common/src/PacketContainer.cpp
	      ${CMAKE_CURRENT_SOURCE_DIR}/../common/src/Protocol.cpp
	      ${CMAKE_CURRENT_SOURCE_DIR}/../common/src/PacketFactory.cpp
	      ${CMAKE_CURRENT_SOURCE_DIR}/../common/src/Singleton.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/includes/)
include_directories(${SFML_INCLUDE_DIR})

set(COM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common/src)


if (!${SOCKET_LIB_ADDED})
	if (UNIX)
		 add_library(socket
		   STATIC
		   ${COM_DIR}/TcpSocket.cpp
		   ${COM_DIR}/TcpSocketUnix.cpp
		   ${COM_DIR}/UdpSocket.cpp
		   ${COM_DIR}/UdpSocketUnix.cpp
		   ../common/includes/PacketContainer.h
		 )
	endif (UNIX)

	if (WIN32)
		 add_library(socket
		   STATIC
		   ${COM_DIR}/TcpSocket.cpp
		   ${COM_DIR}/TcpSocketWin.cpp
		   ${COM_DIR}/UdpSocket.cpp
		   ${COM_DIR}/UdpSocketWin.cpp
		   )
	endif (WIN32)

endif()

add_definitions(-D __CLIENT__)

if (UNIX)
 add_definitions(-g3)
endif(UNIX)

add_executable(client ${src} ${headers})
target_link_libraries(client ${SFML_LIBRARIES})
target_link_libraries(client socket)
target_link_libraries(client thread)