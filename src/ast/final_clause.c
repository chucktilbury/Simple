

/*
    Production being parsed:

final_clause
    : 'final' '(' IDENT ')' function_body
    ;
    
 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_final_clause(ast_final_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

