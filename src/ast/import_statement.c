/**
 *
 * @file import_statement.c
 *
 * @brief Traverse AST for node import_statement.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

/**
 *
 * Grammar production:
 *
 * import_statement
 *     : 'import' formatted_strg 'as' IDENT
 *     ;
 */
void traverse_import_statement(ast_import_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->ident);
    traverse_formatted_strg(node->str, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}
