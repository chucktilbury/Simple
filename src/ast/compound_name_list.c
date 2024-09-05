/**
 *
 * @file compound_name_list.c
 *
 * @brief Traverse AST for node compound_name_list.
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
 * compound_name_list
 *     : '(' ( compound_name (',' compound_name )* )? ')'
 *     ;
 */
void traverse_compound_name_list(ast_compound_name_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_compound_name_t* name;
    int mark = 0;

    while(NULL != (name = iterate_ptr_lst(node->list, &mark)))
        traverse_compound_name(name, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

