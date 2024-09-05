/**
 *
 * @file list_init_str.c
 *
 * @brief Traverse AST for node list_init_str.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

/**
 *
 * Grammar production:
 *
 * list_init_str
 *     : LITERAL_DSTR
 *     | LITERAL_SSTR
 *     ;
 */
void traverse_list_init_str(ast_list_init_str_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->str);

    CALL_NODE_FUNC(post);
    RET;
}

