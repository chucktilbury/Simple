

/*
    Production being parsed:

namespace_definition
    : 'namespace' IDENT '{' ( namespace_item )+ '}'
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_namespace_definition(ast_namespace_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

