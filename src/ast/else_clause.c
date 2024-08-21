

/*
    Production being parsed:

else_clause
    : 'else' '(' expression ')' function_body
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_else_clause(ast_else_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

