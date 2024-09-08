/**
 *
 * @file literal_value.c
 *
 * @brief Traverse AST for node literal_value.
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
 * literal_value
 *     : LITERAL_FLOAT
 *     | LITERAL_INTEGER
 *     | LITERAL_BOOL
 *     | string_literal
 *     ;
 */
void traverse_literal_value(ast_literal_value_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    if(node->literal != NULL)
        TRACE_TERMINAL(node->literal);
    else if(node->str != NULL)
        traverse_string_literal(node->str, pre, post);
    else FATAL("never ever happens");

    CALL_NODE_FUNC(post);
    RET;
}

