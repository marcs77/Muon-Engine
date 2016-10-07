file(GLOB_RECURSE MUON_CORE_INCLUDE "*.h")
file(GLOB_RECURSE MUON_CORE_SRC "*.cpp")

include_directories (.)

include_directories (../dependencies/glfw/include)
include_directories (../dependencies/glad/include)
include_directories (../dependencies/FreeImage/include)
include_directories (../dependencies/freetype/include)
include_directories (../dependencies/freetype-gl)

add_library(MuonCore ${MUON_CORE_SRC} ${MUON_CORE_INCLUDE})

target_link_libraries(MuonCore glfw ${GLFW_LIBRARIES})
target_link_libraries(MuonCore glad)
target_link_libraries(MuonCore freetype)
target_link_libraries(MuonCore freetype-gl)
target_link_libraries(MuonCore ${CMAKE_SOURCE_DIR}/dependencies/FreeImage/libs/freeimage)

link_directories(${CMAKE_SOURCE_DIR}/dependencies/FreeImage/libs)

#file(COPY ${CMAKE_SOURCE_DIR}/dependencies/FreeImage/libs/FreeImage.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


