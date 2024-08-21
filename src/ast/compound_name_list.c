

/*
    Production being parsed:

compound_name_list
    : '(' ( compound_name (',' compound_name )* )? ')'
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_compound_name_list(ast_compound_name_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

