

/*
    Production being parsed:

class_definition
    : 'class' IDENT ( '(' ( type_name )? ')' )? '{' ( class_item )+ '}'
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_class_definition(ast_class_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

