/**
 *
 * @file create_name.c
 *
 * @brief Traverse AST for node create_name.
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
 * create_name
 *     : IDENT ('.' IDENT)? '.' 'create'
 *     ;
 */
void traverse_create_name(ast_create_name_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

