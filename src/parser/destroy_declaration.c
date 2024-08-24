/**
 *
 * @file destroy_declaration.c
 *
 * @brief Parse grammar production destroy_declaration.
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
 * destroy_declaration
 *     : ('virtual' )? 'destroy'
 *     ;
 */
ast_destroy_declaration_t* parse_destroy_declaration(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_destroy_declaration_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    bool is_virtual;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE(state);
                if(TOK_VIRTUAL == TTYPE) { 
                    consume_token();
                    is_virtual = true;
                }
                else
                    is_virtual = false;
                state = 1;
                break;

            case 1:
                TRACE_STATE(state);
                if(TOK_DESTROY == TTYPE) { 
                    consume_token();
                    state = 100;
                }
                else 
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_destroy_declaration_t*)create_ast_node(AST_DESTROY_DECLARATION);
                node->is_virtual = is_virtual;
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

