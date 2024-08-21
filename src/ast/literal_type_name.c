

/*
    Production being parsed:

 literal_type_name
    : 'float'
    | 'integer'
    | 'string'
    | 'boolean'
    | 'nothing'
    | 'list'
    | 'dict'
    ;

*/
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_literal_type_name(ast_literal_type_name_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

