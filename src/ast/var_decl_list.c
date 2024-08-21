

/*
    Production being parsed:

 var_decl_list
    : '(' ( var_decl ( ',' var_decl )* )? ')'
    ;

*/
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_var_decl_list(ast_var_decl_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

