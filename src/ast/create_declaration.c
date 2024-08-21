/**
 *
 * @file create_declaration.c
 *
 * @brief Traverse AST for node create_declaration.
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
 * create_declaration
 *     : ('virtual' )? 'create' type_name_list
 *     ;
 */
void traverse_create_declaration(ast_create_declaration_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

