

/*
    Production being parsed:

list_init_element
    : list_init_str ':' assignment_item
    | assignment_item
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_list_init_element(ast_list_init_element_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

