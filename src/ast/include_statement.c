

/*
    Production being parsed:

include_statement
    : 'include' formatted_strg
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_include_statement(ast_include_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

