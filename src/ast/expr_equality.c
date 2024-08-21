

/*
    Production being parsed:

expr_equality
    : expr_compare '==' expr_compare
    | expr_compare '!=' expr_compare
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_expr_equality(ast_expr_equality_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

