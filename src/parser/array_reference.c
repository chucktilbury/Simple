/**
 *
 * @file array_reference.c
 *
 * @brief Parse grammar production array_reference.
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
 * array_reference
 *     : IDENT array_param_list
 *     ;
 */
ast_array_reference_t* parse_array_reference(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_array_reference_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* name;
    ast_array_param_list_t* list;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    name = copy_token(get_token());
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                // get the param list
                if(NULL != (list = parse_array_param_list(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_array_reference_t*)create_ast_node(AST_ARRAY_REFERENCE);
                node->ident = name;
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

