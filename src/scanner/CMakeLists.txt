cmake_minimum_required(VERSION 3.10)
project(scanner)

#set(CMAKE_VERBOSE_MAKEFILE ON)
include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

add_library(${PROJECT_NAME} STATIC
    fileio.c
    scanner.c
    token_defs.c
    tokens.c
)

