

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
#include "tokens.h"
#include "errors.h"
#include "parser.h"

ast_function_body_element_t* parse_function_body_element(void) {

    ENTER;

    ast_function_body_element_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE(state);
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_function_body_element_t*)create_ast_node(AST_FUNCTION_BODY_ELEMENT);
                finished = true;
                break;

            case 101:
                // not a match, not an error
                TRACE_STATE(state);
                reset_token_queue(post);
                finished = true;
                break;

            case 102:
                // error found
                TRACE_STATE(state);
                recover_error();
                finished = true;
                break;

            default:
                FATAL("unknown state: %d", state);
        }
    }

    RETURN(node);
}

