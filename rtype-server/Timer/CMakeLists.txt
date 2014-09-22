cmake_minimum_required (VERSION 2.8)

include_directories(./includes/)

set (src Clock.cpp)

if (UNIX)
   set (src
	UnixTimer.cpp
    ${src}
    )
elseif (WIN32)
    set (src
	WinTimer.cpp
    ${src}
)
endif()
   
add_library(timer
  STATIC 
  ${src}
)

if (UNIX)
	target_link_libraries(timer rt)
endif()
