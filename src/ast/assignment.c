

/*
    Production being parsed:

assignment
    : compound_reference '=' assign_eq_item
    | compound_reference '+=' assign_inc_item
    | compound_reference '-=' expression
    | compound_reference '*=' expression
    | compound_reference '/=' expression
    | compound_reference '%=' expression
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_assignment(ast_assignment_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

