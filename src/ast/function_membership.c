/**
 * @file function_membership.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-13
 * 
 * @copyright Copyright (c) 2024
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
 * function_membership
 *     : compound_name ':' 
 *     ;
 */
void traverse_function_membership(ast_function_membership_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_compound_name(node->name, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

