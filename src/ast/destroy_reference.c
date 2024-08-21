

/*
    Production being parsed:

destroy_reference
    : destroy_name
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_destroy_reference(ast_destroy_reference_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

