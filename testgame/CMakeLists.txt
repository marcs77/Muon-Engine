project(TestGame)

include_directories ("../core")

file(GLOB MUON_GAME_INCLUDE "*.h")
file(GLOB MUON_GAME_SRC "*.cpp")

include_directories (../dependencies/glfw/include)
include_directories (../dependencies/glad/include)
include_directories (../dependencies/FreeImage/include)
include_directories (../dependencies/freetype/include)
include_directories (../dependencies/freetype-gl)
include_directories (../dependencies/assimp/include)

add_executable (TestGame ${MUON_GAME_SRC} ${MUON_GAME_INCLUDE})

target_link_libraries (TestGame freetype MuonCore)
set_property(TARGET TestGame PROPERTY CXX_STANDARD 14)

file(COPY ./resources DESTINATION ${PROJECT_BINARY_DIR}/workingDir)
