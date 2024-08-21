

/*
    Production being parsed:

 import_statement
    : 'import' formatted_strg 'as' IDENT
    ;

*/
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_import_statement(ast_import_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

