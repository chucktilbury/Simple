

/*
    Production being parsed:

namespace_item
    : scope_operator
    | namespace_definition
    | class_definition
    | function_definition
    | create_definition
    | destroy_definition
    | var_definition
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_namespace_item(ast_namespace_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

