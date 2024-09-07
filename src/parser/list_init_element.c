/**
 *
 * @file list_init_element.c
 *
 * @brief Parse grammar production list_init_element.
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
 * list_init_element
 *     : list_init_str ':' assignment_item
 *     | assignment_item
 *     ;
 */
ast_list_init_element_t* parse_list_init_element(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_list_init_element_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    // this is NULL if there is no str
    ast_list_init_str_t* str = NULL;
    ast_assignment_item_t* item = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(NULL != (str = parse_list_init_str(pstate)))
                    state = 1;
                else
                    state = 2;
                break;

            case 1:
                // look for a ':'
                TRACE_STATE;
                if(TOK_COLON == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else 
                    state = 101;
                break;

            case 2:
                // assignment item
                TRACE_STATE;
                if(NULL != (item = parse_assignment_item(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_list_init_element_t*)create_ast_node(AST_LIST_INIT_ELEMENT);
                // this is NULL if there is no str
                node->str = str;
                node->item = item;
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

