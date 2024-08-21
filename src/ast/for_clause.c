

/*
    Production being parsed:

for_clause
    : 'for' ( '(' ( (type_name)? IDENT 'in' expression )? ')' )? function_body
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_for_clause(ast_for_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

