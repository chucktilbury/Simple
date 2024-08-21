

/*
    Production being parsed:

expr_primary
    : literal_value
    | compound_reference
    | cast_statement
    | '(' expression ')'
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_expr_primary(ast_expr_primary_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

