cmake_minimum_required(VERSION 3.10)
project(parse_test)

#set(CMAKE_VERBOSE_MAKEFILE OFF)

add_executable(${PROJECT_NAME}
    parse_test.c
)

target_link_libraries(${PROJECT_NAME}
    pthread
    parse
    scan
    ast
    util
    gc
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -DUSE_GC
        -I${PROJECT_SOURCE_DIR}/..
        -I${PROJECT_SOURCE_DIR}/../../src/util
        -I${PROJECT_SOURCE_DIR}/../../src/util/gc/include
        -I${PROJECT_SOURCE_DIR}/../../src/parse
        -I${PROJECT_SOURCE_DIR}/../../src/scanner
        -I${PROJECT_SOURCE_DIR}/../../src/ast
        -I${PROJECT_SOURCE_DIR}/../../src/misc
        -I${CMAKE_CURRENT_BINARY_DIR}/../../src/scanner
        $<$<CONFIG:DEBUG>:-g >
        $<$<CONFIG:DEBUG>:-DENABLE_LOGGER >
        $<$<CONFIG:DEBUG>:-DUSE_TRACE >
        $<$<CONFIG:RELEASE>:-Ofast >
        $<$<CONFIG:PROFILE>:-pg -O0 >
)
