cmake_minimum_required(VERSION 2.8)

project(rtype)

message("THIS IS RTYPE")

##detecting system
if (UNIX)
  message("Building for Unix...")
elseif (WIN32)
  message("Building for Windows...")
else()
  message(SEND_ERROR "Your system is not supported. :(")
endif()


###special flags
if (UNIX)
  add_definitions(-Wwrite-strings)
  add_definitions(-std=c++0x)
endif()

###SFML INTEGRATION FOR CLIENT

if (WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
endif()

if (WIN32)
  set(SFML_ROOT "C:\\SFML\\SFML-1.6")
  set(SFML_INCLUDE_DIR "C:\\SFML\\SFML-1.6\\include")
  set(SFML_LIBRARY_DIR "C:\\SFML\\SFML-1.6\\lib\\vc2008")
endif()

#find sfml install directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

set(SFML_LIBRARIES ${SFML_SYSTEM_LIBRARY} ${SFML_WINDOW_LIBRARY} ${SFML_GRAPHICS_LIBRARY} ${SFML_NETWORK_LIBRARY} ${SFML_AUDIO_LIBRARY})
include_directories(${SFML_INCLUDE_DIR})

###SETTING BINARY OUTPUT DIRECTORY 

##UNIX
if (UNIX)
  set(PROJECT_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
  set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}")
endif()


##for MSVC
if (WIN32)
  foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
  endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
endif()

add_subdirectory(common)
add_subdirectory(rtype-client)
add_subdirectory(rtype-server)
