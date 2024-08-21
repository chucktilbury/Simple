

/*
    Production being parsed:

class_item
    : scope_operator
    | var_decl
    | function_declaration
    | create_declaration
    | destroy_declaration
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_class_item(ast_class_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

