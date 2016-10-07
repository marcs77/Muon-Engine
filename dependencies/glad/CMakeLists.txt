file(GLOB_RECURSE GLAD_INCLUDE "*.h")
file(GLOB_RECURSE GLAD_SRC "*.c")

include_directories (include)

add_library(glad ${GLAD_SRC} ${GLAD_INCLUDE})

