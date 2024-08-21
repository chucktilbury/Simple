

/*
    Production being parsed:
    
raise_statement
    : 'raise' '(' IDENT ',' string_literal ')'
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_raise_statement(ast_raise_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

