

/*
    Production being parsed:

 var_definition
    : ( 'const' )? var_decl ( '=' assignment_item )?
    ;

*/
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_var_definition(ast_var_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

