/**
 *
 * @file array_param.c
 *
 * @brief Parse grammar production array_param.
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
 * array_param
 *     : '[' array_param_item ']'
 *     ;
 */
ast_array_param_t* parse_array_param(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_array_param_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_array_param_item_t* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(TOK_OSBRACE == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                // get the item
                TRACE_STATE;
                if(NULL != (ptr = parse_array_param_item(pstate)))
                    state = 2;
                else
                    state = 101;
                break;

            case 2:
                // get a ']' or its an error
                TRACE_STATE;
                if(TOK_CSBRACE == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ']'");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_array_param_t*)create_ast_node(AST_ARRAY_PARAM);
                node->item = ptr;
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
