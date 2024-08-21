

/*
    Production being parsed:

 formatted_strg
    : LITERAL_DSTR ( expression_list )?
    ;

*/
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_formatted_strg(ast_formatted_strg_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

