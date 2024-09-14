/**
 *
 * @file function_body.c
 *
 * @brief Parse grammar production function_body.
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
 * function_body
 *     : '{' ( function_body_element )* '}'
 *     ;
 */
ast_function_body_t* parse_function_body(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_function_body_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* list = create_ptr_lst();
    ast_function_body_element_t* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_OCBRACE == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(NULL != (ptr = parse_function_body_element(pstate)))
                    append_ptr_lst(list, ptr);
                else if(TOK_CCBRACE == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a function body statement or a '}'");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_function_body_t*)create_ast_node(AST_FUNCTION_BODY);
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
