
project(ast)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

file(GLOB_RECURSE ast_xxfiles
    ${PROJECT_SOURCE_DIR}/*.c
)

add_library(${PROJECT_NAME} STATIC
    ${ast_xxfiles}
)


