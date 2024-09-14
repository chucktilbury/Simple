/**
 *
 * @file function_body.c
 *
 * @brief Traverse AST for node function_body.
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
 * function_body
 *     : '{' ( function_body_element )* '}'
 *     ;
 */
void traverse_function_body(ast_function_body_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_function_body_element_t* ele;
    int mark = 0;

    while(NULL != (ele = iterate_ptr_lst(node->list, &mark)))
        traverse_function_body_element(ele, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}
