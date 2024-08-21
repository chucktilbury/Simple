/**
 *
 * @file list_init_element.c
 *
 * @brief Traverse AST for node list_init_element.
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
 * list_init_element
 *     : list_init_str ':' assignment_item
 *     | assignment_item
 *     ;
 */
void traverse_list_init_element(ast_list_init_element_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

