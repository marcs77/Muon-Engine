file(GLOB_RECURSE MUON_CORE_INCLUDE "*.h")
file(GLOB_RECURSE MUON_CORE_SRC "*.cpp")

file(GLOB M_BASE "*.cpp" "*.h")
file(GLOB M_GRAPHICS "graphics/*.cpp" "graphics/*.h")
file(GLOB M_GRAPHICS_BUFFER "graphics/buffer/*.cpp" "graphics/buffer/*.h")
file(GLOB M_GRAPHICS_TEXT "graphics/text/*.cpp" "graphics/text/*.h")
file(GLOB M_GRAPHICS_LAYER "graphics/layer/*.cpp" "graphics/layer/*.h")
file(GLOB M_INPUT "input/*.cpp" "input/*.h")
file(GLOB M_MATH "math/*.cpp" "math/*.h")
file(GLOB M_UTIL "util/*.cpp" "util/*.h")

source_group("" FILES ${MUON_CORE_SRC} ${MUON_CORE_INCLUDE})
source_group("graphics" FILES ${M_GRAPHICS})
source_group("graphics\\buffer" FILES ${M_GRAPHICS_BUFFER})
#source_group("graphics\\text" FILES ${M_GRAPHICS_TEXT})
#source_group("graphics\\layer" FILES ${M_GRAPHICS_LAYER})
source_group("input" FILES ${M_INPUT})
source_group("math" FILES ${M_MATH})
source_group("util" FILES ${M_UTIL})


include_directories (.)

include_directories (../dependencies/glfw/include)
include_directories (../dependencies/glad/include)
include_directories (../dependencies/FreeImage/include)
include_directories (../dependencies/freetype/include)
include_directories (../dependencies/freetype-gl)

add_library(MuonCore ${MUON_CORE_SRC} ${MUON_CORE_INCLUDE})

set_property(TARGET MuonCore PROPERTY CXX_STANDARD 14)


target_link_libraries(MuonCore glfw ${GLFW_LIBRARIES})
target_link_libraries(MuonCore glad)
target_link_libraries(MuonCore freetype)
target_link_libraries(MuonCore freetype-gl)

if(WIN32 OR WIN64)
	target_link_libraries(MuonCore ${CMAKE_SOURCE_DIR}/dependencies/FreeImage/libs/freeimage)
	link_directories(${CMAKE_SOURCE_DIR}/dependencies/FreeImage/libs)
else()
	target_link_libraries(MuonCore freeimage)
endif()

#file(COPY ${CMAKE_SOURCE_DIR}/dependencies/FreeImage/libs/FreeImage.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


