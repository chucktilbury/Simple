/**
 *
 * @file module.c
 *
 * @brief Parse grammar production module.
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
 * module
 *     : ( module_item )+
 *     ;
 */
ast_module_t* parse_module(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_module_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_module_item_t* ptr;
    PtrLst* list = create_ptr_lst();

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(NULL != (ptr = parse_module_item(pstate))) {
                    append_ptr_lst(list, ptr);
                    state = 1;
                }
                else 
                    state = 102;
                break;

            case 1:
                TRACE_STATE;
                if(NULL != (ptr = parse_module_item(pstate)))
                    append_ptr_lst(list, ptr);
                else if(TTYPE == TOK_END_OF_FILE)
                    state = 100;
                else
                    state = 102;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_module_t*)create_ast_node(AST_MODULE);
                node->list = list;
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

