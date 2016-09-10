project(MuonEngine)
cmake_minimum_required(VERSION 3.1)

find_package(Freetype REQUIRED)

aux_source_directory(. SRC_LIST)
file(GLOB_RECURSE MUONSRC ./src/*.cpp)
file(GLOB_RECURSE MUONH ./src/*.h)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${MUONSRC} ${MUONH})
add_subdirectory(./Dependencies/glfw-3.2.1)
add_subdirectory(./Dependencies/freetype-2.6)
add_subdirectory(./Dependencies/freetype-gl)
#add_subdirectory(./Dependencies/FreeImage)
include_directories(./Dependencies/glfw-3.2.1/include)
include_directories(./Dependencies/glad/include)
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(./Dependencies/freetype-gl)
#include_directories(./Dependencies/FreeImage/Source)

target_link_libraries(MuonEngine glfw ${GLFW_LIBRARIES})
target_link_libraries(MuonEngine ${FREETYPE_LIBRARIES})
target_link_libraries(MuonEngine freetype-gl)
target_link_libraries(MuonEngine freeimage)

set (CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")
