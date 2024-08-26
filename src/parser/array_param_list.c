/**
 *
 * @file array_param_list.c
 *
 * @brief Parse grammar production array_param_list.
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
 * array_param_list
 *     : array_param (array_param)*
 *     ;
 */
ast_array_param_list_t* parse_array_param_list(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_array_param_list_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* list = create_ptr_lst();
    ast_array_param_t* ptr;

    while(!finished) {
        switch(state) {
            case 0:
                // zero or more array_param
                TRACE_STATE;
                if(NULL != (ptr = parse_array_param(pstate))) {
                    append_ptr_lst(list, ptr);
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                // get more of them
                TRACE_STATE;
                if(NULL != (ptr = parse_array_param(pstate))) {
                    append_ptr_lst(list, ptr);
                }
                else
                    state = 100; // finished
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_array_param_list_t*)create_ast_node(AST_ARRAY_PARAM_LIST);
                node->ptr = list;
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

