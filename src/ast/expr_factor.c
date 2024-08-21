

/*
    Production being parsed:

expr_factor
    : expr_unary '*' expr_unary
    | expr_unary '/' expr_unary
    | expr_unary '%' expr_unary
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_expr_factor(ast_expr_factor_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

