

/*
    Production being parsed:

destroy_declaration
    : ('virtual' )? 'destroy'
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_destroy_declaration(ast_destroy_declaration_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

