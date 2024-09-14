/**
 *
 * @file var_decl.c
 *
 * @brief Traverse AST for node var_decl.
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
 * var_decl
 *     : type_name IDENT
 *     ;
 */
void traverse_var_decl(ast_var_decl_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->ident);
    traverse_type_name(node->type, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}
