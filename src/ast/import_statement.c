/**
 *
 * @file import_statement.c
 *
 * @brief Traverse AST for node import_statement.
 * This file was generated on Wed Aug 21 09:35:58 2024.
 *
 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

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

    CALL_NODE_FUNC(post);
    RET;
}

