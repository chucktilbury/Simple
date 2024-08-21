

/*
    Production being parsed:

if_clause
    : 'if' '(' expression ')' function_body ( else_clause )* ( final_else_clause )?
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_if_clause(ast_if_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

