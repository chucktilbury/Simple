

/*
    Production being parsed:

create_definition
    : ('virtual' )? create_name var_decl_list function_body
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_create_definition(ast_create_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

