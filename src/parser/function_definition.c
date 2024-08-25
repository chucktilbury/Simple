/**
 *
 * @file function_definition.c
 *
 * @brief Parse grammar production function_definition.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "tokens.h"
#include "errors.h"
#include "parser.h"

/**
 *
 * Grammar production:
 *
 * function_definition
 *     : ('virtual' )? compound_name var_decl_list var_decl_list function_body
 *     ;
 */
ast_function_definition_t* parse_function_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_function_definition_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    bool is_virtual;
    ast_compound_name_t* name;
    ast_var_decl_list_t* inp;
    ast_var_decl_list_t* outp;
    ast_function_body_t* body;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE(state);
                if(TOK_VIRTUAL == TTYPE) {
                    is_virtual = true;
                    consume_token();
                }
                state = 1;
                break;

            case 1:
                TRACE_STATE(state);
                if(NULL != (name = parse_compound_name(pstate))) 
                    state = 2;
                else
                    state = 101;
                break;

            case 2:
                TRACE_STATE(state);
                if(NULL != (inp = parse_var_decl_list(pstate))) 
                    state = 3;
                else 
                    state = 101;
                break;

            case 2:
                TRACE_STATE(state);
                if(NULL != (outp = parse_var_decl_list(pstate))) 
                    state = 3;
                else {
                    EXPECTED("a variable declaration list");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE(state);
                if(NULL != (body = parse_function_body(pstate)))
                    state = 100;
                else {
                    EXPECTED("a function body");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_function_definition_t*)create_ast_node(AST_FUNCTION_DEFINITION);
                node->is_virtual = is_virtual;
                node->name = name;
                node->inp = inp;
                node->outp = outp;
                node->body = body;
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

