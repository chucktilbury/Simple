/**
 *
 * @file create_reference.c
 *
 * @brief Traverse AST for node create_reference.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

/**
 *
 * Grammar production:
 *
 * create_reference
 *     : IDENT ( '.' IDENT )* '.' 'create' expression_list
 *     ;
 */
void traverse_create_reference(ast_create_reference_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    int mark = 0;
    Token* ident;

    while(NULL != (ident = iterate_ptr_lst(node->name, &mark)))
        TRACE_TERMINAL(ident);
    traverse_expression_list(node->inp, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}
