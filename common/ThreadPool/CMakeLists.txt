cmake_minimum_required (VERSION 2.8)

include_directories(../includes/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../includes/)

set (src ThreadPool.cpp)

if (UNIX)
  set(LIBRARY_OUTPUT_PATH ../../../bin)
   set (src
    ${src}
    Mutex.cpp
    UnixMutex.cpp
    UnixThread.cpp
	LockGuard.cpp
    )
elseif (WIN32)
    set (src
    ${src}
    Mutex.cpp
    Win32Mutex.cpp
    Win32Thread.cpp
	LockGuard.cpp
)
endif()
   
add_library(thread 
  STATIC 
  ${src}
)

if (UNIX)
   target_link_libraries(thread pthread)
endif()