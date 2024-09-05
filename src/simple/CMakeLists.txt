project(simple)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

add_executable(${PROJECT_NAME}
    main.c
)

target_link_libraries(${PROJECT_NAME}
    parser
    scanner
    ast
    errors
    common
    gc
    pthread
)


