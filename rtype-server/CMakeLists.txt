cmake_minimum_required(VERSION 2.8)

add_subdirectory(Timer)

set(LIBRARY_OUTPUT_PATH ./../common/lib)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(COM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common/src)

file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/includes/*)
file(GLOB headers_common ${CMAKE_CURRENT_SOURCE_DIR}/../common/includes/*)

set(src
	${SRC_DIR}/ABehaviour.cpp
	${SRC_DIR}/ActionManager.cpp
	${SRC_DIR}/Connexion.cpp
	${SRC_DIR}/Game.cpp
	${SRC_DIR}/GameObject.cpp
	${SRC_DIR}/hexdump.cpp
	${SRC_DIR}/main.cpp
	${SRC_DIR}/NetworkManager.cpp
	${SRC_DIR}/Room.cpp
	${SRC_DIR}/Map.cpp
	${SRC_DIR}/RoomManager.cpp
	${SRC_DIR}/Server.cpp
	${SRC_DIR}/ServerException.cpp
	${SRC_DIR}/TcpServer.cpp
	${SRC_DIR}/GameObjectFactory.cpp
	${SRC_DIR}/BehaviourFactory.cpp
	${SRC_DIR}/ClientBehaviour.cpp
	${SRC_DIR}/WallBehaviour.cpp
	${SRC_DIR}/BulletBehaviour.cpp
	${SRC_DIR}/SineBasicEnnemy.cpp
	${SRC_DIR}/FireingEnnemy.cpp
	${SRC_DIR}/MapCreationMethod.cpp
	${SRC_DIR}/MobSpawner.cpp

	${COM_DIR}/Logger.cpp
	${COM_DIR}/PacketContainer.cpp
	${COM_DIR}/PacketFactory.cpp
	${COM_DIR}/Protocol.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/includes/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Timer/includes/)

if (UNIX)
  add_definitions(-std=c++0x)
  add_definitions(-g3)
elseif(WIN32)
  #add_definitions(-idunnolol)
endif()


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
		SET(SOCKET_LIB_ADDED TRUE)
	endif (UNIX)

	if (WIN32)
		add_library(socket
		  STATIC
		  ${COM_DIR}/TcpSocket.cpp
		  ${COM_DIR}/TcpSocketWin.cpp
		  ${COM_DIR}/UdpSocket.cpp
		  ${COM_DIR}/UdpSocketWin.cpp
		  )	
		SET(SOCKET_LIB_ADDED TRUE)
	endif (WIN32)
endif()

if (UNIX)
	set(src ${src} TcpServerUnix.cpp)
endif()

if (WIN32)
	set(src ${src} TcpServerWin.cpp)
endif()

add_definitions(-D __SERVER__)

add_executable(server ${src} ${headers} ${headers_common})
target_link_libraries(server socket)
target_link_libraries(server timer)
target_link_libraries(server thread)
