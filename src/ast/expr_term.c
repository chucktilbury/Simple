

/*
    Production being parsed:

expr_term
    : expr_factor '+' expr_factor
    | expr_factor '-' expr_factor
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_expr_term(ast_expr_term_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

