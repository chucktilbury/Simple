

/*
    Production being parsed:

function_body_element
    : var_definition
    | function_reference
    | create_reference
    | destroy_reference
    | assignment
    | while_clause
    | do_clause
    | for_clause
    | if_clause
    | try_clause
    | switch_clause
    | break_statement
    | continue_statement
    | INLINE
    | yield_statement
    | type_statement
    | return_statement
    | raise_statement
    | trace_statement
    | print_statement
    | function_body
    ;

 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

void traverse_function_body_element(ast_function_body_element_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

