project(scanner_test)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

include_directories(
    "${PROJECT_SOURCE_DIR}/../../src/ast"
    "${PROJECT_SOURCE_DIR}/../../src/common"
    "${PROJECT_SOURCE_DIR}/../../src/scanner"
    "${PROJECT_SOURCE_DIR}/../../src/tokens"
    "${PROJECT_SOURCE_DIR}/../../src/parser"
    "${PROJECT_SOURCE_DIR}/../../src/errors"
    "${PROJECT_SOURCE_DIR}/../../src/symbols"
)

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



