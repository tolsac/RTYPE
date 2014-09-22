set(COM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.[h,hh,hpp])

add_subdirectory(ThreadPool)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes/)

if (UNIX)
	set(LIBRARY_OUTPUT_PATH ../../bin)
	add_library(socket
	  STATIC
	  ${COM_DIR}/TcpSocket.cpp
	  ${COM_DIR}/TcpSocketUnix.cpp
	  ${COM_DIR}/UdpSocket.cpp
	  ${COM_DIR}/UdpSocketUnix.cpp
	  ${headers}
	)
endif (UNIX)

if (WIN32)
	add_library(socket
	  STATIC
	  ${COM_DIR}/TcpSocket.cpp
	  ${COM_DIR}/TcpSocketWin.cpp
	  ${COM_DIR}/UdpSocket.cpp
	  ${COM_DIR}/UdpSocketWin.cpp
	  ${headers}
	  )
endif (WIN32)

set(SOCKET_LIB_ADDED TRUE)
set(THREAD_LIB_ADDED TRUE)
