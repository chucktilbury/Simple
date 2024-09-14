/**
 *
 * @file destroy_reference.c
 *
 * @brief Traverse AST for node destroy_reference.
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
 * destroy_reference
 *     : IDENT ( '.' IDENT )* '.' 'destroy'
 *     ;
 */
void traverse_destroy_reference(ast_destroy_reference_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    int mark = 0;
    Token* ident;
    
    while(NULL != (ident = iterate_ptr_lst(node->name, &mark)))
        TRACE_TERMINAL(ident);

    CALL_NODE_FUNC(post);
    RET;
}

