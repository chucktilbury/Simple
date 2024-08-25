/**
 *
 * @file list_init_str.c
 *
 * @brief Parse grammar production list_init_str.
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
 * list_init_str
 *     : LITERAL_DSTR
 *     | LITERAL_SSTR
 *     ;
 */
ast_list_init_str_t* parse_list_init_str(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_list_init_str_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* str;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE(state);
                if(TOK_LITERAL_DSTR == TTYPE) {
                    str = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_LITERAL_SSTR == TTYPE) {
                    str = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else 
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_list_init_str_t*)create_ast_node(AST_LIST_INIT_STR);
                node->str = str;
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

