/**
 *
 * @file function_declaration.c
 *
 * @brief Traverse AST for node function_declaration.
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
 * function_declaration
 *     : ('virtual' )? IDENT type_name_list type_name_list
 *     ;
 */
void traverse_function_declaration(ast_function_declaration_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

