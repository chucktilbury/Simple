project(scanner)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

flex_target(lexer scan.l "${CMAKE_CURRENT_BINARY_DIR}/scan.c")
#bison_target(parser parse.y "${CMAKE_CURRENT_BINARY_DIR}/parse.c")

add_definitions(
    -Wno-sign-compare 
    -Wno-unused-variable 
    -Wno-implicit-function-declaration 
    -Wno-parentheses-equality
)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_BINARY_DIR}/scan.c
)

target_link_libraries(${PROJECT_NAME}
)


