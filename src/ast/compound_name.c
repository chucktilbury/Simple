/**
 *
 * @file compound_name.c
 *
 * @brief Traverse AST for node compound_name.
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
 * compound_name
 *     : IDENT ( '.' IDENT )*
 *     ;
 */
void traverse_compound_name(ast_compound_name_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    Token* id;
    int mark = 0;

    while(NULL != (id = iterate_ptr_lst(node->list, &mark)))
        TRACE_TERMINAL(id);

    CALL_NODE_FUNC(post);
    RET;
}

