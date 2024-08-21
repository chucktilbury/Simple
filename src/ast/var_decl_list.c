/**
 *
 * @file var_decl_list.c
 *
 * @brief Traverse AST for node var_decl_list.
 * This file was generated on Wed Aug 21 09:35:58 2024.
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
 * var_decl_list
 *     : '(' ( var_decl ( ',' var_decl )* )? ')'
 *     ;
 */
void traverse_var_decl_list(ast_var_decl_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

