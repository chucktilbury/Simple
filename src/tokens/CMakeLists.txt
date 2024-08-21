project(tokens)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

add_library(${PROJECT_NAME} STATIC
    token_symbols.c
    token_queue.c
    token_defs.c
)

#add_custom_command(
#    OUTPUT token_symbols.c token_symbols.h
#    COMMENT "Make a sorted list of the tokens and associated infrastructure."
#    COMMAND python ${PROJECT_SOURCE_DIR}/mk_tokens.py
#                    ${PROJECT_SOURCE_DIR}/keywords.txt
#                    ${PROJECT_SOURCE_DIR}/token_symbols.h.template
#                    ${PROJECT_SOURCE_DIR}/token_symbols.c.template
#    #SOURCES keywords.txt
#    DEPENDS mk_tokens.py keywords.txt token_symbols.c.template token_symbols.h.template
#)
