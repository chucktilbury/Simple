/*
 * All of the ast node functions.
 */

#include "common.h"
#include "ast.h"

void traverse_ast(AstNode* node, AstFuncPtr pre, AstFuncPtr post) {

    ASSERT(node != NULL);
    ASSERT(pre != NULL);
    ASSERT(post != NULL);

    ENTER;

    RET;
}

