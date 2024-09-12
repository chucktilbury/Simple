
project(symbols)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

file(GLOB_RECURSE symbols_xxfiles
    ${PROJECT_SOURCE_DIR}/*.c
)

add_library(${PROJECT_NAME} STATIC
    ${symbols_xxfiles}
)



