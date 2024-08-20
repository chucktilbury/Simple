
project(errors)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

add_library(${PROJECT_NAME} STATIC
    errors.c        
)


