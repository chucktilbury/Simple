/**
 *
 * @file create_declaration.c
 *
 * @brief Parse grammar production create_declaration.
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
 * create_declaration
 *     : ('virtual' )? 'create' type_name_list
 *     ;
 */
ast_create_declaration_t* parse_create_declaration(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_create_declaration_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_type_name_list_t* inp = NULL;
    bool is_virtual = false;

    while(!finished) {
        switch(state) {
            case 0:
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
                if(TOK_CREATE == TTYPE) { 
                    consume_token();
                    state = 2;
                }
                else 
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (inp = parse_type_name_list(pstate))) {
                    state = 100;
                }
                else {
                    EXPECTED("a parameter list");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_create_declaration_t*)create_ast_node(AST_CREATE_DECLARATION);
                node->inp = inp;
                node->is_virtual = is_virtual;
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

