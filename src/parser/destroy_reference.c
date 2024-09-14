/**
 *
 * @file destroy_reference.c
 *
 * @brief Parse grammar production destroy_reference.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "errors.h"
#include "parser.h"
#include "tokens.h"

/**
 *
 * Grammar production:
 *
 * destroy_reference
 *     : IDENT ( '.' IDENT )* '.' 'destroy'
 *     ;
 */
ast_destroy_reference_t* parse_destroy_reference(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_destroy_reference_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* name = create_ptr_lst();

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    append_ptr_lst(name, copy_token(get_token()));
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                // mandatory '.'
                TRACE_STATE;
                if(TOK_DOT == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    append_ptr_lst(name, copy_token(get_token()));
                    consume_token();
                    state = 1;
                }
                else if(TOK_DESTROY == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_destroy_reference_t*)create_ast_node(AST_DESTROY_REFERENCE);
                node->name = name;
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
