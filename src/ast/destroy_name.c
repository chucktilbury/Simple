/**
 *
 * @file destroy_name.c
 *
 * @brief Traverse AST for node destroy_name.
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
 * destroy_name
 *     : IDENT ('.' IDENT)? '.' 'destroy'
 *     ;
 */
void traverse_destroy_name(ast_destroy_name_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    Token* tok;
    int mark = 0;

    while(NULL != (tok = iterate_ptr_lst(node->ident, &mark)))
        TRACE_TERMINAL(tok);

    CALL_NODE_FUNC(post);
    RET;
}

