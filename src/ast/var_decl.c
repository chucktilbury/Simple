/**
 *
 * @file var_decl.c
 *
 * @brief Traverse AST for node var_decl.
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
 * var_decl
 *     : type_name IDENT
 *     ;
 */
void traverse_var_decl(ast_var_decl_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

