cmake_minimum_required(VERSION 2.6)
project(MuonEngine)

if(WIN32 OR WIN64)
	find_package(freetype REQUIRED)
else()
	find_package(Freetype REQUIRED)
endif()

set(MuonEngine_VERSION_MAJOR 0)
set(MuonEngine_VERSION_MINOR 1)

option(BUILD_GAME "Build game." "testgame")

configure_file (
  "${PROJECT_SOURCE_DIR}/build_info.h.in"
  "${PROJECT_BINARY_DIR}/build_info.h"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
message("cxx flags: " ${CMAKE_CXX_FLAGS})

include_directories(${PROJECT_BINARY_DIR})


#Dependencies
add_subdirectory (dependencies/glfw)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples." FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests." FORCE)

add_subdirectory (dependencies/glad)
add_subdirectory (dependencies/freetype)
add_subdirectory (dependencies/freetype-gl)
add_subdirectory (dependencies/assimp)

set_property(TARGET glfw PROPERTY FOLDER "dependencies")
set_property(TARGET glad PROPERTY FOLDER "dependencies")
set_property(TARGET freetype PROPERTY FOLDER "dependencies")
set_property(TARGET freetype-gl PROPERTY FOLDER "dependencies")
set_property(TARGET assimp PROPERTY FOLDER "dependencies")

#Engine
add_subdirectory (core)

message("Building ${BUILD_GAME}")
add_subdirectory(${BUILD_GAME})

if(WIN32 OR WIN64)
	file(COPY ${CMAKE_SOURCE_DIR}/dependencies/FreeImage/libs/FreeImage.dll DESTINATION ${PROJECT_BINARY_DIR}/workingDir)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${PROJECT_BINARY_DIR}/workingDir)
