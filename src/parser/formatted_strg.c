/**
 *
 * @file formatted_strg.c
 *
 * @brief Parse grammar production formatted_strg.
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
 * formatted_strg
 *     : LITERAL_DSTR ( expression_list )?
 *     ;
 */
ast_formatted_strg_t* parse_formatted_strg(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_formatted_strg_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* str;
    ast_expression_list_t* exprs = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_LITERAL_DSTR == TTYPE) {
                    str = copy_token(get_token());
                    consume_token();
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                exprs = parse_expression_list(pstate);
                state = 100;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_formatted_strg_t*)create_ast_node(AST_FORMATTED_STRG);
                node->str = str;
                node->exprs = exprs;
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

