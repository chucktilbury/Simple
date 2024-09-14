/**
 * @file alias_definition.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

/**
 * Grammar production:
 *
 * alias_definition
 *      : compound_name 'as' IDENT
 *      ;
 */
void traverse_alias_definition(ast_alias_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->ident);
    traverse_compound_name(node->target, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}
