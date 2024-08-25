/**
 *
 * @file list_init.c
 *
 * @brief Parse grammar production list_init.
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
 * list_init
 *     : '[' list_init_element ( ',' list_init_element )* ']'
 *     ;
 */
ast_list_init_t* parse_list_init(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_list_init_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();
    
    ast_list_init_element_t* ptr;
    PtrLst* list = create_ptr_lst();

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE(state);
                if(TOK_OSBRACE == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                // required element
                TRACE_STATE(state);
                if(NULL != (ptr = parse_list_init_element(pstate)))
                    state = 2;
                else {
                    EXPECTED("a list initialization element");
                    state = 102;
                }
                break;

            case 2:
                // either a ',' or a ']'
                TRACE_STATE(state);
                if(TOK_COMMA == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else if(TOK_CSBRACE == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ',' or a ']'");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_list_init_t*)create_ast_node(AST_LIST_INIT);
                node->list = list;
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

