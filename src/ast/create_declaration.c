/**
 *
 * @file create_declaration.c
 *
 * @brief Traverse AST for node create_declaration.
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
 * create_declaration
 *     : ('virtual' )? 'create' type_name_list
 *     ;
 */
void traverse_create_declaration(ast_create_declaration_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE("is_virtual = %s", node->is_virtual? "true": "false");
    traverse_type_name_list(node->inp, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

