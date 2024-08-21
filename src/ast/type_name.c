

/*
    Production being parsed:

 type_name
    : literal_type_name
    | compound_name
    ;

*/
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_type_name(ast_type_name_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

