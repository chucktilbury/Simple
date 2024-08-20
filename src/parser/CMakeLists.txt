project(parser)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

file(GLOB_RECURSE parser_xxfiles
    ${PROJECT_SOURCE_DIR}/*.c
)

add_library(${PROJECT_NAME} STATIC
    ${parser_xxfiles}
)


