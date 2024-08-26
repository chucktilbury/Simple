/**
 *
 * @file create_definition.c
 *
 * @brief Parse grammar production create_definition.
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
 * create_definition
 *     : ('virtual' )? create_name var_decl_list function_body
 *     ;
 */
ast_create_definition_t* parse_create_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_create_definition_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    bool is_virtual = false;
    ast_create_name_t* name;
    ast_var_decl_list_t* inp;
    ast_function_body_t* body;

    while(!finished) {
        switch(state) {
                // initial state
                TRACE_STATE;
                if(TOK_VIRTUAL == TTYPE) { 
                    consume_token();
                    is_virtual = true;
                }
                else
                    is_virtual = false;
                state = 1;
                break;

            case 1:
                TRACE_STATE;
                if(NULL != (name = parse_create_name(pstate))) 
                    state = 2;
                else 
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (inp = parse_var_decl_list(pstate)))
                    state = 3;
                else {
                    EXPECTED("the input definitions");
                    state = 102;
                }
                break;
            
            case 3:
                TRACE_STATE;
                if(NULL != (body = parse_function_body(pstate)))
                    state = 100;
                else {
                    EXPECTED("a function body");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_create_definition_t*)create_ast_node(AST_CREATE_DEFINITION);
                node->is_virtual = is_virtual;
                node->name = name;
                node->inp = inp;
                node->body = body;
                finished = true;
                break;

            case 101:
                // not a match, not an error
                TRACE_STATE;
                reset_token_queue(post);
                finished = true;
                break;

            case 102:
                // error found
                TRACE_STATE;
                recover_error();
                finished = true;
                break;

            default:
                FATAL("unknown state: %d", state);
        }
    }

    RETURN(node);
}

